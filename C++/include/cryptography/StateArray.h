#pragma once

#include <PCH.h>


static const int size = 4;

namespace QPP {
    class StateArray {
    public:
        StateArray();

        uint8_t getValueAt(int row, int col);
        void setValueAt(int row, int col, int value);

        // TODO - Under construction
        uint8_t galoisVectorMix(std::array<uint8_t, size> & a);
    private:
        std::array<std::array<uint8_t, size>, size> matrix;
    };
}