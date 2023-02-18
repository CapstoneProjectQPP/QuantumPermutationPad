#include "cryptography/QuantumPermutationPad.h"

namespace QPP {
    
    // The seed should be of size M*n*2^n
    QuantumPermutationPad::QuantumPermutationPad(std::vector<int> seed) {

        if(seed.size() != (params::M * params::n * params::mat_len)) {
            exit(1);
        }
        this->seed = seed;

        // Create M permutation matrices
        for(int i = 0; i < params::M; i++) {
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
        uint8_t S[params::mat_size];

        for(int i = 0; i < params::mat_size; i++) {
            S[i] = i;
        }
        uint8_t offset = key_index * params::mat_size;
        for(int i = params::mat_size - 1; i == 1; i--) {
            uint8_t j = this->seed[offset+i];

            uint8_t tmp = S[j];
            S[j] = S[i];
            S[i] = tmp;

        }
        for(int i = 0; i < params::mat_size; i++) {
            this->permutationGates[key_index].setValueAt(i, S[i], 1);
        }

    }
    
    // Generate a random number using LSFR with the seed
    void QuantumPermutationPad::prng() {
        //convert seed to int
        
        int result = 0;
        for (auto d : seed)  
        {
            result = result * 10 + d;
        }
        //generate pseudo random number based on seed
        if (result < 0) {
            result = -result;
        }

        result++;
        result = result*15485863;
        rng_output_int =  (result*result*result)%2038074743;
        //store into rng_output array
        for(int i = 0; i < params::n; i++) {
            this->rng_output[i] = (rng_output_int >> i) & 1;
        }

    }

    int QuantumPermutationPad::prng(int lo, int hi) {
        return 0;
    }
    
    // Select one permutation matrix to multiply with plain text vector
    void QuantumPermutationPad::dispatch() {
        int d = rng_output_int % params::M;
        PermutationMatrix gate = this->permutationGates[d];
        this->plain_text_vector = gate.multiply(this->plain_text_vector);
    }
    
    // Generate a plain text messsage column vector. This involves an XOR with
    // n plaintext bits with n random bits from the prng. The result should be
    // mapped to one column vector from the computational basis.
    void QuantumPermutationPad::generateVector(std::string plain_text) {
        for(int i = 0; i < params::n; i++) {
            
            this->plain_text_vector[i] = (plain_text[i] - '0') ^ this->rng_output[i];
        }

    }

    
    std::string QuantumPermutationPad::getResult() {
        return "";
    }

}
