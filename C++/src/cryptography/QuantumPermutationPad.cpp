#include "cryptography/QuantumPermutationPad.h"

namespace QPP {
    
    // The seed should be of size M*n*2^n
    QuantumPermutationPad::QuantumPermutationPad(std::vector<int> seed) {
        this->seed = seed;
    }

    // Encrypt plain text into cipher text uinsg protected functions
    std::string QuantumPermutationPad::encrypt(std::string& plain_text) {
        return "";
    }
            
    // Decrypt cipher text into plain text uinsg protected functions
    std::string QuantumPermutationPad::decrypt(std::string& cipher_text) {
        return "";
    }

    // Generate M permutation matrices using the seed (shared secret key)
    // https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
    void QuantumPermutationPad::fisherYatesShuffle() {
        int a[size];
        a[0] = 1;
        for(int i = 1; i < size; i++) {
            a[i] = 0;
        }

        int tmp_arr[size];
        // Create M permutation matrices
        for(int i = 0; i < M; i++) {
            std::copy(a, a+size, tmp_arr);
            for(int j = 0; j < size; j++) {
                int x;
                for(int k = size-1; k == 0; k--) {
                    // Find random number between 0 and i
                    x = prng(0, k);
                    // Swap a[x] and a[k]
                    int tmp = tmp_arr[k];
                    tmp_arr[k] = tmp_arr[x];
                    tmp_arr[x] = tmp;
                }
                for(int k = 0; k < size; k++) {
                    this->permutationGates[i].setValueAt(j, k, tmp_arr[k]);
                }
            }
        }

    }
    
    // Generate a random number using LSFR with the seed
    void QuantumPermutationPad::prng() {
        
    }

    int QuantumPermutationPad::prng(int lo, int hi) {
        return 0;
    }
    
    // Select one permutation matrix to multiply with plain text vector
    void QuantumPermutationPad::dispatch() {
        
    }
    
    // Generate a plain text messsage column vector. This involves an XOR with
    // n plaintext bits with n random bits from the prng. The result should be
    // mapped to one column vector from the computational basis.
    void QuantumPermutationPad::generateVector(std::string plain_text) {


    }

    
    std::string QuantumPermutationPad::getResult() {
        return "";
    }

}
