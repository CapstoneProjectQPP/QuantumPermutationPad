#pragma once

#include <PCH.h>
#define n 8
#define M 64
#define size (2 << n)



namespace QPP {
    class PermutationMatrix {
    public:

        uint8_t getValueAt(int row, int col);
        void setValueAt(int row, int col, int value);

    private:
        std::array<std::array<uint8_t, size>, size> matrix;
    };
}
