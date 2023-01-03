#include "cryptography/AES.h"


namespace QPP {
    template<class T>
    std::string AES<T>::encrypt(std::string plain_text, std::string key, int key_size) {

        std::cout << "Encrypting" << std::endl;
        return "";
    }
}

template class QPP::AES<int>;