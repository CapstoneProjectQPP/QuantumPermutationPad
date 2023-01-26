#include <PCH.h>

#include "cryptography/AES.h"


int main() {

    // std::cout << "Hello World" << std::endl;

    QPP::AES aes;

    std::string input = "Hello Wrorld";
    std::string key = "abcdefghijklmnop";
    std::cin >> input;
    std::cin >> key;
    std::string result = aes.encrypt(input, key, 128);
    std::cout << result << std::endl;
    return 0;
}


