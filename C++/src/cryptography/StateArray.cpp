#include "cryptography/StateArray.h"


QPP::StateArray::StateArray() {
    matrix = std::vector<std::vector<uint8_t>>(4);
    for (int i = 0; i < 4; i++) {
        matrix[i] = std::vector<uint8_t>(4);
    }
}
