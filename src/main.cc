#include "/public/read.h" // IWYU pragma: keep
#include <boost/beast/http/impl/verb.ipp>
#include <vector>         // IWYU pragma: keep
#include <functional>
#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/beast.hpp>
#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/multiprecision/fwd.hpp>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/random.hpp>
#include <boost/integer/common_factor.hpp>

#include "../client/Encryptdatboi.h"

using namespace boost::multiprecision;
using namespace boost::random;
using tcp = boost::asio::ip::tcp;
using namespace boost::multiprecision;
using namespace std;
namespace websocket = boost::beast::websocket;

 //Prime test function
cpp_int prime_test(cpp_int num) {
	if (miller_rabin_test(num, 50)) {
  		if (miller_rabin_test(num-1/2, 50))
		return num;
     } else {
		num += 2;
		prime_test(num);
	 }
	}

cpp_int encode(const function<cpp_int(string)>& func, string val) {
	return func(val);
}

string decode(const function<string(cpp_int)>& func, cpp_int val) {
	return func(val);
}

cpp_int encrypt(const function<cpp_int(PrivateKey, cpp_int)>& func, PrivateKey pk, cpp_int val) {
	return func(pk, val);
}

cpp_int decrypt(const function<cpp_int(PublicKey, cpp_int)>& func, PublicKey pk, cpp_int val) {
	return func(pk, val);
}

cpp_int signMessage(cpp_int message, cpp_int privateExponent, cpp_int modulus) {
	return powm(message, privateExponent, modulus);
}

cpp_int modInverse(cpp_int a, cpp_int m) {
    cpp_int m0 = m;
    cpp_int y = 0, x = 1;

    if (m == 1) return 0;

    while (a > 1) {
        cpp_int q = a / m;
        cpp_int t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0) x += m0;
    return x;
}

int main() {
	int port = 6969;
	//Two very large prime numbers
	cpp_int p = 0;
	cpp_int q = 0;
	boost::mt19937 mt;
	boost::random::uniform_int_distribution<cpp_int> gen(0, cpp_int(1)<<256);
	
	p = gen(mt);
	while(true) {
		if (p % 2 == 0) {
			p = gen(mt);
		} else {
			break;
		}
	}
	
	p = prime_test(p);


	while(true) {
		if (q % 2 == 0) {
			q = gen(mt);
		} else {
			break;
		}
	}

	q = prime_test(q);

	cpp_int t = (p-1) * (q-1);
	cpp_int n = p * q;
	const cpp_int e = 65537;
	// cpp_int d = pow(e, -1) % t;
	cpp_int d = modInverse(e, t);
	cpp_int m = 0; //Email integer (Decrypting is pow(S, D) % N)
	cpp_int s = pow(m,65537);

	try {
		boost::asio::io_context context;
		tcp::acceptor acceptor(context, tcp::endpoint(tcp::v4(),port));
		cout << "Listening on: " << port << endl;
		while(true) {
			tcp::socket socket(context);
			acceptor.accept(socket);
			cout << "Client accepted\n";
			websocket::stream<tcp::socket> ws(move(socket));
			ws.accept();
			while(true) {
				boost::beast::flat_buffer fb;
				ws.read(fb);
				string message = boost::beast::buffers_to_string(fb.data());
				cout << "Received: " << message << endl;
				string response = "";
				string val = message.substr(2, string::npos);
				cpp_int numVal(val);
				switch(message.at(0)) {
					case '1':
						response = "1-" + encrypt(/*yourfuncHere*/, numVal).str();  
						break;
					case '2':
						response = "2-" + decrypt(/*yourfuncHere*/, numVal).str();  
						break;
					case '3':
						response = "3-" + encode(stringToint, val).str();  
						break;
					case '4': 
						response = "4-" + decode(intTostring, numVal);  
						break;
					case '5': {
						response = "5-" + signMessage(numVal, d, n).str();
						break;
					}
					default:
						cerr << "Malphormed data: " << message << endl;
						exit(1);
				}
				ws.text(true);
				ws.write(boost::asio::buffer(response));
			}
		}
	}
	catch(const exception& err) {
		cerr << "Server error: " << err.what() << endl;
	}
	
	
}
