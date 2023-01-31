#include "cryptography/PermutationMatrix.h"


namespace QPP {

        uint8_t PermutationMatrix::getValueAt(int row, int col){
            return 0;
        }
        void PermutationMatrix::setValueAt(int row, int col, int value){
            this.matrix[row][col] = value;
        }
}
