#pragma once

#include <PCH.h>

static const int n = 8;
static const int size = 2 << n;

namespace QPP {
    class PermutationMatrix {
    public:
        PermutationMatrix();

        uint8_t getValueAt(int row, int col);
        void setValueAt(int row, int col, int value);

    private:
        std::array<std::array<uint8_t, size>, size> matrix;
    };
}
