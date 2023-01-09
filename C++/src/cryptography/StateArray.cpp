#include "cryptography/StateArray.h"


QPP::StateArray::StateArray() {
}

uint8_t QPP::StateArray::getValueAt(int row, int col) {
    return matrix[row][col];
}

void QPP::StateArray::setValueAt(int row, int col, int value) {
    matrix[row][col] = value;
}

std::array<uint8_t, size> QPP::StateArray::getColumn(int col) {
    std::array<uint8_t, size> column;
    for (int i = 0; i < size; i++) {
        column[i] = matrix[i][col];
    }
    return column;
}
std::array<uint8_t,size> QPP::StateArray::galoisVectorMix(const std::array<uint8_t, size> &a) {

    // TODO
    return 0;
}

