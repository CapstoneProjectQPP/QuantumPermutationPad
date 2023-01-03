#include <PCH.h>

#include "cryptography/AES.h"


int main() {

    std::cout << "Hello World" << std::endl;

    QPP::AES<int> aes;
    aes.encrypt("Something", "Key", 256);

    return 0;
}


