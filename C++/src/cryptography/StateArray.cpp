#include "cryptography/StateArray.h"


QPP::StateArray::StateArray() {
}

uint8_t QPP::StateArray::getValueAt(int row, int col) {
    return matrix[row][col];
}

uint8_t QPP::StateArray::setValueAt(int row, int col, int value) {
    matrix[row][col] = value;
}

