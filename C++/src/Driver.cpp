#include <PCH.h>

#include "cryptography/AES.h"


int main() {

    std::cout << "Hello World" << std::endl;

    QPP::AES aes;

    std::string input = "something";
    std::string key = "abcdefghijklmnop";
    aes.encrypt(input, key, 128);

    return 0;
}


