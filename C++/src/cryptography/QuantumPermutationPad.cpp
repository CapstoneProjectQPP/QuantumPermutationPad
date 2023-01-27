#include "cryptography/QuantumPermutationPad.h"

namespace QPP {
    
    // The seed should be of size M*n*2^n
    QuantumPermutationPad::QuantumPermutationPad(std::string seed) {
        this->seed = seed;
    }

    // Encrypt plain text into cipher text uinsg protected functions
    std::string QuantumPermutationPad::encrypt(std::string& plain_text) {

    }
            
    // Decrypt cipher text into plain text uinsg protected functions
    std::string QuantumPermutationPad::decrypt(std::string& cipher_text) {

    }

    // Generate M permutation matrices using the seed (shared secret key)
    void QuantumPermutationPad::fisherYatesShuffle() {
        
    }
    
    // Generate a random number using LSFR with the seed
    void QuantumPermutationPad::prng() {
        
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
        
    }

}
