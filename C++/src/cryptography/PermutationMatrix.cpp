#include "cryptography/PermutationMatrix.h"




namespace QPP {

        PermutationMatrix::PermutationMatrix() {
            for(int i = 0; i < params::mat_len; i++) {
                for(int j = 0; j < params::mat_len; j++) {
                    this->matrix[i][j] = 0;
                }
            }
        }

        uint8_t PermutationMatrix::getValueAt(int row, int col){
            return 0;
        }
        void PermutationMatrix::setValueAt(int row, int col, int value){
            this->matrix[row][col] = value;
        }
        std::array<uint8_t, params::mat_len> PermutationMatrix::multiply (std::array<uint8_t, params::mat_len> vector){
            std::array<uint8_t, params::mat_len> result;
            for(int i = 0; i < params::mat_len; i++) {
                for(int j = 0; j < params::mat_len; j++) {
                    result[i] += this->matrix[i][j] * vector[j];
                }
            }
            return result;
        }
        //transpose the permutation matrix and return a new one
        PermutationMatrix PermutationMatrix::transpose(){
            PermutationMatrix result;
            for(int i = 0; i < params::mat_len; i++) {
                for(int j = 0; j < params::mat_len; j++) {
                    result.setValueAt(i, j, this->matrix[j][i]);
                }
            }
            return result;
        }

        


        
}
