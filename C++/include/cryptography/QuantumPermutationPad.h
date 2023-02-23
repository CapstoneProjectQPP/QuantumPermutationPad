#pragma once

#include <PCH.h>
#include "PermutationMatrix.h"


namespace QPP {
    class QuantumPermutationPad {
        public:
            
            QuantumPermutationPad(std::vector<int> seed);

            /**
            * Encrypt a string called plain text using a string key.
            *
            * @param plain_text
            * @param key
            * @param key_size
            * @return
            */  
            std::string encrypt(std::string& plain_text);

            /**
            * Decrypt a string called plain text using a string key.
            *
            * @param plain_text
            * @param key
            * @param key_size
            * @return
            */
            std::string decrypt(std::string& cipher_text);

            

            /* TODO - move to protected*/
            void generateMatrix(uint8_t key_index);
            void prng();
            void prng(std::array<int, params::mat_len> seed);
            void dispatch();
            void generateVector(std::string plain_text);
            std::string getResult();


        private:
            // std::array<int, params::n> rng_output;
            std::vector<std::array<int, params::mat_len>> rng_output_vector;
            std::string plain_text;
            std::vector<int> seed;
            std::array<PermutationMatrix, params::mat_len> permutationGates;
            long long int rng_output_int;
            std::vector<std::array<uint8_t, params::mat_len>> plain_text_vector;
            std::vector<std::array<uint8_t, params::mat_len>> cipher_text_vector;//store the cipher text after each permutation gate

    };
}