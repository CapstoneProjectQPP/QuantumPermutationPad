#pragma once

#include <PCH.h>
#include "StateArray.h"

namespace QPP {
    class QuantumPermutationPad {
        public:

            std::string encrypt();
            std::string decrypt();

            /* TODO - move to protected*/
            void FisherYatesShuffle();
            void PRNG();
            void Dispatch();
            std::string getResult();


        private:

            std::string* plain_text;
            std::string* key;
            int key_size;
            StateArray stateArray;
            StateArray keyArray;
    };
}