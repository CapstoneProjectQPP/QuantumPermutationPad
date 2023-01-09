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
std::array<uint8_t,size> QPP::StateArray::galoisVectorMix(const std::array<uint8_t, size> &r) {
    // TODO
    std::array<uint8_t, size> a;
    std::array<uint8_t, size> b;
    uint8_t h;

    for(int ii = 0; ii < size; ii++) {
      a.at(ii) = r.at(ii);
      h = (uint8_t)((r.at(ii) >> 7) & 1);
      b.at(ii) = r.at(ii) << 1;
      b.at(ii) ^= h * 0x1B;
    }
    
    std::array<uint8_t, size> result;
    result.at(0) = b.at(0) ^ a.at(3) ^ a.at(2) ^ b.at(1) ^ a.at(1);
    result.at(1) = b.at(1) ^ a.at(0) ^ a.at(3) ^ b.at(2) ^ a.at(2);
    result.at(2) = b.at(2) ^ a.at(1) ^ a.at(0) ^ b.at(3) ^ a.at(3);
    result.at(3) = b.at(3) ^ a.at(2) ^ a.at(1) ^ b.at(0) ^ a.at(0);

    return result;
}

