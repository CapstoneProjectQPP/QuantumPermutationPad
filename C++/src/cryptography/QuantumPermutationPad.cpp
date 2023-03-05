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
        //Current, the plain text should be a multiple of n, with no padding
        //the M permutatition matrix is genereated by the constructor usiong the seed
        //generate a vector of plain text
        this->generateVector(plain_text);
        //dispatch the plain text vector to the permutation matrix
        this->dispatch();
        //convert the cipher text vector to a string
        std::string cipher_text;
        for (auto each : this->cipher_text_vector) {
            for (auto bit : each)  
            {
                cipher_text += bit;
            }
        }
        return cipher_text;
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
        std::array<int, params::mat_len> rng_output;
        for(int i = 0; i < params::mat_len; i++) {
            rng_output[i] = (rng_output_int >> i) & 1;
        }
        //push into rng_output_vector
        this->rng_output_vector.push_back(rng_output);

    }

    void QuantumPermutationPad::prng(std::array<int, params::mat_len> seed) {
        //generate pseudo random number based on previous generated random number as a seed
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
        std::array<int, params::mat_len> rng_output;
        for(int i = 0; i < params::mat_len; i++) {
            rng_output[i] = (rng_output_int >> i) & 1;
        }
        //push into rng_output_vector
        this->rng_output_vector.push_back(rng_output);
    }
    
    // Select one permutation matrix to multiply with plain text vector
    void QuantumPermutationPad::dispatch() {
        //for each of the plaintext vector, select a random permutation matrix
        //to multiply with, and then push to cipher text vector
        int index = 0;
        for (auto each : this->plain_text_vector) {
            int d = 0;
            for (auto bit : rng_output_vector[index])  
            {
                d = d * 10 + bit;
            }
            index++;//index to the next random number
            d = d % params::M;
            PermutationMatrix gate = this->permutationGates[d];
            this->cipher_text_vector.push_back(gate.multiply(each));
        }
        
    }
    
    // Generate a plain text messsage column vector. This involves an XOR with
    // n plaintext bits with n random bits from the prng. The result should be
    // mapped to one column vector from the computational basis.
    void QuantumPermutationPad::generateVector(std::string plain_text) {
        for (int i = 0; i < sizeof(plain_text); i+=params::mat_len) {
            if (plain_text[i] == '\n' || plain_text[i] == '\0'){
                //need some sort of padding here
                break;
            }
            //assume we have plain text just right to be a multiple of n
            else{
                std::array<uint8_t, params::mat_len> tmp;
                for(int j = i; j < params::mat_len; j++) {
                    //generate a new random number
                    if (j == 0) {
                        this->prng();
                    }
                    else{
                        this->prng(this->rng_output_vector.back());
                    }
                    //xor with prng, -'0' to convert char to int, ASCII
                    tmp[j] = (plain_text[j] - '0') ^ this->rng_output_vector.back()[j];
                }
                //push to the plain text vector
                this->plain_text_vector.push_back(tmp);
            }

        }
      

    }

    
    std::string QuantumPermutationPad::getResult() {
        return "";
    }

}
