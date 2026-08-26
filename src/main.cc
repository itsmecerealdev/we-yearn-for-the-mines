#include "/public/read.h" // IWYU pragma: keep
#include <boost/multiprecision/fwd.hpp>
#include <vector>         // IWYU pragma: keep
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
using namespace boost::multiprecision;
using namespace boost::random;
using namespace std;
 
cpp_int prime_test(cpp_int num) {
	if (miller_rabin_test(num, 50)) {
  		return num;
     } else {
		num += 2;
		prime_test(num);
	 }

}

int main() {
	//Two very large prime numbers
	cpp_int p = 0;
	cpp_int q = 0;

	mt19937 mt
	uniform_int_distribution<cpp_int> ui(-(cpp_int(1) << 256), cpp_int(1)<<256);
	for(unsigned i = 0; i < 5; i++)
		ui(mt);
	
	
	cpp_int p = 0;//prime_test();
	cpp_int q = 0;//prime_test();

	cpp_int t = (p-1) * (q-1);
	cpp_int n = p * q;
	const cpp_int e = 65537;
	cpp_int d = pow(e, -1) % T;
	cpp_int m = 0; //Email integer (Decrypting is pow(S, D) % N)
	cpp_int s = pow(m,65537);
}
