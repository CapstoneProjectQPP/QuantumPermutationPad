#pragma once

#include <PCH.h>
#define n                   8
#define M                   64
#define mat_len             (2 << n)
#define mat_size            (mat_len * mat_len)



namespace QPP {
    class PermutationMatrix {
    public:

        uint8_t getValueAt(int row, int col);
        void setValueAt(int row, int col, int value);

    private:
        std::array<std::array<uint8_t, mat_size>, mat_size> matrix;
    };
}
