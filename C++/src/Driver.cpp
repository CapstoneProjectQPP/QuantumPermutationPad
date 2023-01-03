#include <PCH.h>

#include "cryptography/AES.h"


int main() {

    std::cout << "Hello World" << std::endl;

    QPP::AES aes;

    std::string input = "Something";
    std::string key = "Key";
    aes.encrypt(input, key, 256);

    return 0;
}


