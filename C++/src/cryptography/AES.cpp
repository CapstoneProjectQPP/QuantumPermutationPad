#include "cryptography/AES.h"


namespace QPP {
    std::string AES::encrypt(std::string& plain_text, std::string& key, int key_size) {

        this->plain_text = &plain_text;
        this->key = &key;
        this->key_size = key_size;
        parseKey();
        keyExpansion();
        parse();
        subBytes();
        shiftRows();

        return "";
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
        for (int i = 0; i < size; i++) {

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
        for (int round = 0; round < 10; round++){

            //first we need to rotate the last column
            std::array<uint8_t, size> col1 = tempArray.getColumn(size - 1);
            //now we need to shift the column
            //rotate by 1
            /*
            eg.
                    [09]        [cf]
                    [cf]   =>   [4f]  
                    [4f]        [3c]
                    [3c]        [09]
            */
            for (int i = 0; i < size; i++) {
                col1[i] = col1[(i + 1) % size];
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

}