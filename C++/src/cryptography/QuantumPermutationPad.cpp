#include "cryptography/QuantumPermutationPad.h"

namespace QPP {
    
    // The seed should be of size M*n*2^n
    QuantumPermutationPad::QuantumPermutationPad(std::vector<int> seed) {

       if(seed.size() != (params::M * params::n * params::mat_len)) {
           perror("seed size wrong");
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
        //decrtpted the cipher text in the reverse order
        //multiply each item in the cipher_text_vector with the transposed permutation matrix
        //and XOR with its corresponding random number, just like dispatch in the encryption
        TransposeMatrix();
        std::string decrypted_message = "";
        int index = 0;
        for (auto each : this->cipher_text_vector){
            //multiply each item in the cipher_text_vector with the transposed permutation matrix
            int d = 0;
            for (auto bit : rng_output_vector[index])  
            {
                d = d * 10 + bit;
            }
            //index to the next random number
            d = d % params::M;
            if (d < 0) {
                d = -d;
            }
            PermutationMatrix trans_gate = this->permutationGates_transposed[d];
            std::array<uint8_t, params::mat_len> result;
            result = trans_gate.multiply(each);
            //XOR with its corresponding random number
            for(int i = 0; i < params::mat_len; i++) {
                result[i] = (result[i]) ^ rng_output_vector[index][i];

            }
            index++;
            //convert the result to a string
            for (auto bit : result)  
            {
                decrypted_message += bit;
            }

        }
        return decrypted_message;
    }

    // Generate M permutation matrices using the seed (shared secret key)
    // https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
    void QuantumPermutationPad::generateMatrix(uint8_t key_index) {
        uint8_t S[params::mat_len];

        for(int i = 0; i < params::mat_len; i++) {
            S[i] = i;
        }
        uint8_t offset = key_index * params::mat_len;
        for(int i = params::mat_len - 1; i == 1; i--) {
            uint8_t j = this->seed[offset+i];

            uint8_t tmp = S[j];
            S[j] = S[i];
            S[i] = tmp;

        }
        for(int i = 0; i < params::mat_len; i++) {
            this->permutationGates[key_index].setValueAt(i, S[i], 1);
        }

    }

    //for decryption use
    void QuantumPermutationPad::TransposeMatrix() {
        //transpose each of the M permutation matrix and save it to permutationGates_transposed
        for(int i = 0; i < params::M; i++) {
            this->permutationGates_transposed[i] = this->permutationGates[i].transpose();
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
            if (d < 0) {
                d = -d;
            }
            PermutationMatrix gate = this->permutationGates[d];
            this->cipher_text_vector.push_back(gate.multiply(each));
        }
        
    }
    
    // Generate a plain text messsage column vector. This involves an XOR with
    // n plaintext bits with n random bits from the prng. The result should be
    // mapped to one column vector from the computational basis.
    void QuantumPermutationPad::generateVector(std::string plain_text) {
        //assume no padding is used, size of plain text is a multiple of 256
        //first genereate a list of random numbers used for each block of plaintext
        //number of random numbers = number of plaintext blocks
        std::cout<<"size of plain text: "<<plain_text.size()<<std::endl;
        int count = plain_text.size()/ params::mat_len;
        for(int i = 0; i < count; i++) {
            if (i == 0){
                this->prng();
            }
            else{
                this->prng(this->rng_output_vector.back());
            }
        }
        //now that the rng_output_vector is generated, we can start to generate the plaintext vector
        //for each block of plaintext, generate a vector
        int index = 0;
        for (int i = 0; i < plain_text.size(); i+=params::mat_len) {

            if (plain_text[i] == '\n' || plain_text[i] == '\0'){
                //need some sort of padding here
                perror("Reach the end of line\n");

            }
            //assume we have plain text just right to be a multiple of mat_len
            else{
                std::array<uint8_t, params::mat_len> tmp;
                int index_tmp = 0;
                for(int j = i; j < i + params::mat_len; j++) {

                    //generate a new random number
                    //xor with prng, -'0' to convert char to int, ASCII
                    tmp[index_tmp] = (plain_text[j]) ^ this->rng_output_vector[index][index_tmp];
                    index_tmp++;
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
