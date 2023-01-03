#include "cryptography/AES.h"


namespace QPP {
    std::string AES::encrypt(std::string& plain_text, std::string& key, int key_size) {

        this->plain_text = &plain_text;
        this->key = &key;
        this->key_size = key_size;

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

    }
}