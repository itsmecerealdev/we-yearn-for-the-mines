#include "/public/read.h" // IWYU pragma: keep
#include <boost/multiprecision/fwd.hpp>
#include <vector>         // IWYU pragma: keep
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
using namespace boost::multiprecision;
using namespace std;
 
int main() {
	 //Two very large prime numbers
	 cpp_int P = 0;

	cpp_int Q = 0;

	cpp_int T = (P-1) * (Q-1);
	cpp_int N = P * Q;
	const cpp_int E = 65537;
	cpp_int D = pow(E, -1) % T;
	cpp_int M = 0; //Email integer (Decrypting is pow(S, D) % N)
	cpp_int S = pow(M,65537);
 }
