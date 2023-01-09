#pragma once

#include <PCH.h>


static const int size = 4;

namespace QPP {
    class StateArray {
    public:
        StateArray();

        uint8_t getValueAt(int row, int col);
        void setValueAt(int row, int col, int value);
        std::array<uint8_t, size> getColumn(int col);
        // TODO - Under construction
        std::array<uint8_t,size> QPP::StateArray::galoisVectorMix(const std::array<uint8_t, size> &a);
    private:
        std::array<std::array<uint8_t, size>, size> matrix;
    };
}