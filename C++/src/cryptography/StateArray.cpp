#include "cryptography/StateArray.h"


QPP::StateArray::StateArray() {
}

uint8_t QPP::StateArray::getValueAt(int row, int col) {
    return matrix[row][col];
}

void QPP::StateArray::setValueAt(int row, int col, int value) {
    matrix[row][col] = value;
}

uint8_t QPP::StateArray::galoisVectorMix(std::array<uint8_t, size> &a) {

    // TODO
    return 0;
}

