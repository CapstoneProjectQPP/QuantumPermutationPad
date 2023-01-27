#pragma once

#include <PCH.h>
#include "StateArray.h"

namespace QPP {
    class QuantumPermutationPad {
        public:
            
            QuantumPermutationPad(std::string seed);


            void changeSeed(std::string seed);

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
            std::string getResult();


        private:

            std::string plain_text;
            std::string seed;
            int n = 8;
            int M = 64;
            std::vector<StateArray> permuationGates;
            StateArray keyArray;
    };
}