#include "../include/catch2/catch_amalgamated.hpp"
#include "../include/cryptography/AES.h"
#include <iostream>

class AES_mock_encryption : QPP::AES {

    public:
        void init(QPP::StateArray testStateArray, QPP::StateArray KeyArray) {
            stateArray = testStateArray;
            keyArray = KeyArray;
        }

        bool begin_test( QPP::StateArray expected) {


            // Generate keys needed for each round
            keyExpansion();

            // Add round 0 key
            addRoundKey(0);

            // Compute rounds 1 to Nr-1
            for(int i = 1; i <= num_rounds-1; i++) {
                subBytes();
                shiftRows();
                mixColumns();
                addRoundKey(i);
            }

            // Compute round Nr - the final round does not use mixColumns
            subBytes();
            shiftRows();
            addRoundKey(num_rounds);
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    int val1 = stateArray.getValueAt(i,j);
                    int val2 = expected.getValueAt(i, j);
                    if(val1 != val2) {
                        return false;
                    }
                }
            }
            return true;
        }
};



TEST_CASE( "encryption", "[encryption]" ) {

    QPP::StateArray testStateArray1;
    QPP::StateArray expectedResult1,initialKeyArray;
    QPP::StateArray initialArray;
    static const uint8_t initial_matrix[4][10] = {{0x32,0x88,0x31,0xe0},
                                        {0x43,0x5a,0x31,0x37},
                                        {0xf6,0x30,0x98,0x07},
                                        {0xa8,0x8d,0xa2,0x34
                                        }};

    static const uint8_t initial_key[4][10] = {{0x2b,0x28,0xab,0x09},
                                        {0x7e,0xae,0xf7,0xcf},
                                        {0x15,0xd2,0x15,0x4f},
                                        {0x16,0xa6,0x88,0x3c}};                                    

                                      
    static const uint8_t expected[4][10] = {{0x39,0x02,0xdc,0x19},
                                        {0x25,0xdc,0x11,0x6a},
                                        {0x84,0x09,0x85,0x0b},
                                        {0x1d,0xfb,0x97,0x32}};
    

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            initialArray.setValueAt(i, j, (initial_matrix[i][j]));
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            initialKeyArray.setValueAt(i, j, (initial_key[i][j]));
        }
    }
    

     for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            expectedResult1.setValueAt(i, j, (expected[i][j]));
        }
    }

    bool result;
    AES_mock_encryption mockObject;
    
    mockObject.init(initialArray, initialKeyArray);

    // Test 1 - all values should be equal to one
    result = mockObject.begin_test(expectedResult1);
    REQUIRE( result == true );
    
}