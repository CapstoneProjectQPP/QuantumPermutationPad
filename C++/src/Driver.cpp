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
    // std::cout << "081f66d85a5e739b3142e2c2f487a6f0"<< std::endl;
    return 0;
}


