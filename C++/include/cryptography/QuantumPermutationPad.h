#pragma once

#include <PCH.h>
#include "PermutationMatrix.h"

#define n                   8
#define M                   64
#define mat_len             (2 << n)
#define mat_size            (mat_len * mat_len)



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
            int prng(int lo, int hi);
            void dispatch();
            void generateVector(std::string plain_text);
            std::string getResult();


        private:
            std::array<int, n> rng_output;
            std::string plain_text;
            std::vector<int> seed;
            std::array<PermutationMatrix, mat_len> permutationGates;
    };
}