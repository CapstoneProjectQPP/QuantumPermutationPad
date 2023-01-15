#include "cryptography/AES.h"

#define NUM_ROUNDS 10

namespace QPP {
    std::string AES::encrypt(std::string& plain_text, std::string& key, int key_size) {
        this->plain_text = &plain_text;
        this->key = &key;
        this->key_size = key_size;

        // Copy plain text to the state array
        parse();

        // Copy key to the key array
        parseKey();

        // Generate keys needed for each round
        keyExpansion();

        // Add round 0 key
        addRoundKey(0);

        // Compute rounds 1 to Nr-1
        for(int i = 1; i < num_rounds-1; i++) {
            subBytes();
            shiftRows();
            mixColumns();
            addRoundKey(i);
        }

        // Compute round Nr - the final round does not use mixColumns
        subBytes();
        shiftRows();
        addRoundKey(num_rounds);
        
        // Return the encrypted cipher text
        return getResult();
    }

    void AES::parse() {
        int n = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (n < plain_text->size()) {
                    stateArray.setValueAt(i, j, plain_text->at(n));
                    n++;
                }
                else {
                    stateArray.setValueAt(i, j, 0x00);
                }
            }
        }
    }

    void AES::subBytes() {
        StateArray temp;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                uint8_t original = stateArray.getValueAt(i, j);
                uint8_t col = original & 0b00001111;
                uint8_t row = (original & 0b11110000) >> 4;
                temp.setValueAt(i, j, SubstitutionBox[row][col]);
            }
        }
        stateArray = temp;
    }

    void AES::shiftRows() {

        // Rotate 0 row 1
        StateArray temp;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                temp.setValueAt(i, (size + ((j - i) % size)) % size, stateArray.getValueAt(i, j));
            }
        }
        stateArray = temp;
    }

    void AES::mixColumns() {
        StateArray temp;
        std::array<uint8_t, size> col;
        for (int i = 0; i < size; i++) {
            col = stateArray.galoisVectorMix(stateArray.getColumn(i));
            for (int j = 0; j < size; j++) {
                temp.setValueAt(i, j, col[j]);
            }
        }
        stateArray = temp;
    }

    //Adds the round key to the state array using
    //bitwise xor.
    void AES::addRoundKey(int i) {
        StateArray roundKey = keySchedule[i];
        for(int j = 0; j < size; j++) {
            for(int k = 0; k < size; k++) {
                uint8_t value = stateArray.getValueAt(j, k) ^ roundKey.getValueAt(j, k);
                stateArray.setValueAt(j, k, value);
            }
        }
    }


    //pasring the key into a 4x4 matrix
    //similar to the parse method for the state array
    void AES::parseKey() {
        int n = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (n < key->size()) {
                    keyArray.setValueAt(i, j, key->at(n));
                    n++;
                }
                else {
                    keyArray.setValueAt(i, j, 0x00);
                }
            }
        }
    }
    //implementation of key expansion stage
    //we need n+1 keys for n rounds
    //the key schedule is a vector of key state arrays
    void AES::keyExpansion() {
        //init

        StateArray tempArray = keyArray;
        StateArray generatedKeyArray;

        //preserving the original key as round 0
        keySchedule.push_back(keyArray);
        
        //now we need to generate the rest of the keys
        for (int round = 0; round < num_rounds; round++){

            //first we need to rotate the last column
            std::array<uint8_t, size> col1 = tempArray.getColumn(size - 1);
            //now we need to shift the column
            
            /*
            eg.
                    [09]        [cf]
                    [cf]   =>   [4f]  
                    [4f]        [3c]
                    [3c]        [09]
            */
            for (int i = 0; i < size; i++) {
                col1[i] = col1[(((i - 1) % size) + size) % size];
            }
            //now go through the S-box
            for (int j = 0; j < size; j++) {
                col1[j] = SubstitutionBox[(col1[j] & 0b11110000) >> 4][col1[j] & 0b00001111];
            }

            //now xor with the rcon
            for (int j = 0; j < size; j++) {
                col1[j] = col1[j] ^ Rcon[round][j];
            }

            //now xor with the first col
            for (int j = 0; j < size; j++) {
                col1[j] = col1[j] ^ tempArray.getValueAt(0, j);
            }

            //now we need to add the new column to the key schedule
            for (int j = 0; j < size; j++) {
                generatedKeyArray.setValueAt(0, j, col1[j]);
            }

            //now we need to generate the rest of the columns
            for (int i = 1; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    generatedKeyArray.setValueAt(i, j, tempArray.getValueAt(i, j) ^ generatedKeyArray.getValueAt(i - 1, j));
                }
            }

            //now we need to add the generated key to the key schedule
            keySchedule.push_back(generatedKeyArray);
            tempArray = generatedKeyArray;
        }
    }

    // Creates a string containing encrypted ciphertext
    std::string AES::getResult() {
        std::string result;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.append(std::to_string(stateArray.getValueAt(i,j)));
            }
        }
        return result;
    }


}