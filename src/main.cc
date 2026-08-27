#include "/public/read.h" // IWYU pragma: keep
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

cpp_int encode(function<cpp_int(cpp_int)> func, cpp_int val) {
	return func(val);
}

cpp_int decode(function<cpp_int(cpp_int)> func, cpp_int val) {
	return func(val);
}

/*cpp_int encrypt(function<cpp_int(cpp_int)> func, cpp_int val) {
	return func(val);
}

cpp_int decrypt(function<cpp_int(cpp_int)> func, cpp_int val) {
	return func(val);
}*/


cpp_int signMessage(cpp_int message, cpp_int privateExponent, cpp_int modulus) {
	return powm(message, privateExponent, modulus);
}

int main() {
	int port = 6969;
	cpp_int publicKey;
	cpp_int privateKey;
	cpp_int modulus;

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

					
				//	case '1':
				//		response = "1-" + encrypt(/*yourfuncHere*/, numVal).str();  
				//		break;
						
				//	case '2':
				//		response = "2-" + decrypt(/*yourfuncHere*/, numVal).str();  
				//		break;
				//	case '3':
				//		response = "3-" + encode(/*yourfuncHere*/, numVal).str();  
				//		break;
				//	case '4': 
				//		response = "4-" + decode(/*yourfuncHere*/, numVal).str();  
				//		break;

				case '5': {
					cpp_int signature = signMessage(numVal, privateKey, modulus);
					response = "5-" + signature.str();
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
	
	
	//Two very large prime numbers
	cpp_int p = 0;
	cpp_int q = 0;
	boost::mt19937 mt
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
	cpp_int d = pow(e, -1) % T;
	cpp_int m = 0; //Email integer (Decrypting is pow(S, D) % N)
	cpp_int s = pow(m,65537);
}
