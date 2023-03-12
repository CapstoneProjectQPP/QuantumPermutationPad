#include <PCH.h>

#include "cryptography/AES.h"
#include "cryptography/QuantumPermutationPad.h"

void AES_test() {
    QPP::AES aes;
    std::string input = "Hello Wrorld";
    std::string key = "abcdefghijklmnop";
    std::cin >> input;
    std::cin >> key;
    std::string result = aes.encrypt(input, key, 128);
    std::cout << result << std::endl;
}
int main() {

    // std::cout << "Hello World" << std::endl;

    // AES_test();

    //init a seed, size n*M*mat length = 131072
    std::vector<int> *seed = new std::vector<int>();
    for (int i = 0; i < 131072; i++) {
        seed->push_back(i);
    }
    QPP::QuantumPermutationPad *qpp = new QPP::QuantumPermutationPad(*seed);
    std::string plain_text = "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH";
    std::string cipher_text = qpp->encrypt(plain_text);
    std::cout <<"cipher text: " <<cipher_text << std::endl;
    std::string result = qpp->decrypt(cipher_text);
    std::cout <<"deciphered text: " <<result << std::endl;

    //free memory
    delete seed;
    delete qpp;

    return 0;
}


