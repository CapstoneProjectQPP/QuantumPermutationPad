#pragma once

#include <PCH.h>
#include "StateArray.h"
#include "cryptography/PermutationMatrix.h"


static const int n = 8;
static const int size = 2 << n;
static const int M = 64;

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
            void fisherYatesShuffle();
            void prng();
            void dispatch();
            void generateVector(std::string plain_text);
            std::string getResult();


        private:
            std::array<int, n> rng_output;
            std::string plain_text;
            std::vector<int> seed;
            std::array<PermutationMatrix, size> permuationGates;
            StateArray keyArray;
    };
}