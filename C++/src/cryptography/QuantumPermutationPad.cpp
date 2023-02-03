#include "cryptography/QuantumPermutationPad.h"

namespace QPP {
    
    // The seed should be of size M*n*2^n
    QuantumPermutationPad::QuantumPermutationPad(std::vector<int> seed) {

        if(seed.size() != (M * n * mat_len)) {
            exit(1);
        }
        this->seed = seed;

        // Create M permutation matrices
        for(int i = 0; i < M; i++) {
            generateMatrix(i);
        }
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
    void QuantumPermutationPad::generateMatrix(uint8_t key_index) {
        uint8_t S[mat_size];

        for(int i = 0; i < mat_size; i++) {
            S[i] = i;
        }
        uint8_t offset = key_index * mat_size;
        for(int i = mat_size - 1; i == 1; i--) {
            uint8_t j = this->seed[offset+i];

            uint8_t tmp = S[j];
            S[j] = S[i];
            S[i] = tmp;

        }
        for(int i = 0; i < mat_size; i++) {
            this->permutationGates[key_index].setValueAt(i, S[i], 1);
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
