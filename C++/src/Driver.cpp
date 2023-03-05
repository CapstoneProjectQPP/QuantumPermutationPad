#include <PCH.h>

#include "cryptography/AES.h"
#include "cryptography/QuantumPermutationPad.h"

int main() {

    std::cout << "Hello World" << std::endl;

    // QPP::AES aes;

    // std::string input = "Hello Wrorld";
    // std::string key = "abcdefghijklmnop";
    // std::cin >> input;
    // std::cin >> key;
    // std::string result = aes.encrypt(input, key, 128);
    // std::cout << result << std::endl;
    std::vector<int> seed = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    QPP::QuantumPermutationPad qpp(seed);
    // std::string plain_text = "Hello World";
    // std::string cipher_text = qpp.encrypt(plain_text);
    // std::cout << cipher_text << std::endl;

    return 0;
}


