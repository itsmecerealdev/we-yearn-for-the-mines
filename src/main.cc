#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/beast.hpp>

#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/multiprecision/fwd.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <functional>
#include <iostream>
#include <string>

using namespace std;
using tcp = boost::asio::ip::tcp;
using namespace boost::multiprecision;
namespace websocket = boost::beast::websocket;

cpp_int encode(function<cpp_int(cpp_int)> func, cpp_int val) {
	return func(val);
}

cpp_int decode(function<cpp_int(cpp_int)> func, cpp_int val) {
	return func(val);
}

cpp_int encrypt(function<cpp_int(cpp_int)> func, cpp_int val) {
	return func(val);
}

cpp_int decrypt(function<cpp_int(cpp_int)> func, cpp_int val) {
	return func(val);
}

int main() {
	int port = 6969;
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
						response = "3-" + encode(/*yourfuncHere*/, numVal).str();  
						break;
					case '4': 
						response = "4-" + decode(/*yourfuncHere*/, numVal).str();  
						break;
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
