#ifndef ENCRYPTDATBOI_H
#define ENCRYPTDATBOI_H
#include <boost/multiprecision/cpp_int.hpp>
#include <stdexcept>
using namespace std;
using boost::multiprecision::cpp_int;

struct PublicKey {
    cpp_int exponent; // public exponent
    cpp_int modulus; // modulus
};

struct PrivateKey {
    cpp_int exponent; // private exponent
    cpp_int modulus; // modulus
};

struct RSAKeyPair {
    PublicKey publicKey;
    PrivateKey privateKey;
    cpp_int p; // prime number p
    cpp_int q; // prime number q
    cpp_int phi; // (p-1)*(q-1)
};

inline cpp_int modPow(cpp_int base, cpp_int exponent, const cpp_int& modulus) {
	return boost::multiprecision::powm(base, exponent, modulus);
}

inline cpp_int greatestCommonDivisor(cpp_int left, cpp_int right) {
	return boost::multiprecision::gcd(left, right);
}

inline cpp_int encrypt(const cpp_int& message, const PublicKey& publicKey) {
    if (message < 0 || message >= publicKey.modulus) {
        throw std::invalid_argument("Message must be in the range [0, modulus)");
    }
    return boost::multiprecision::powm(message, publicKey.e, publicKey.modulus);

}

inline cpp_int decrypt(const cpp_int& encryptedMessage, const PrivateKey& privateKey) {
    if (encryptedMessage < 0 || encryptedMessage >= privateKey.modulus) {
        throw std::invalid_argument("Encrypted message must be in the range [0, modulus)");
    }
    return boost::multiprecision::powm(encryptedMessage, privateKey.exponent, privateKey.modulus);
}

inline cpp_int stringToint(const string& text) {
    cpp_int value = 0;
    for (char c : text) {
        value <<= 8;
        value += static_cast<unsigned char>(c);
    }
    return value;
}

inline string intTostring(cpp_int value) {
    string text;
    while (value > 0) {
        unsigned int characterVal = (value & 0xFF).convert_to<unsigned int>();
        text += static_cast<char>(characterVal);
        value >>= 8;
    }
    reverse(text.begin(), text.end());
    return text;
}

#endif
