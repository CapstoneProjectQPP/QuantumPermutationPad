#include "../include/catch2/catch_amalgamated.hpp"
#include "../include/cryptography/AES.h"
#include <iostream>

class AES_mock_key_expan : QPP::AES {

    public:
        void init(QPP::StateArray testStateArray) {
            keyArray = testStateArray;
        }

        bool begin_test( QPP::StateArray expected) {
            // stateArray = initialArray;
            this->keyExpansion();
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    int val1 = keySchedule.back().getValueAt(i,j);
                    int val2 = expected.getValueAt(i, j);
                    if(val1 != val2) {
                        return false;
                    }
                }
            }
            return true;
        }
};



TEST_CASE( "keyExpansion", "[keyExpansion]" ) {

    QPP::StateArray testStateArray1;
    QPP::StateArray expectedResult1;
    QPP::StateArray initialArray;
    static const uint8_t initial_matrix[4][10] = {{0x2b,0x28,0xab,0x09},
                                        {0x7e,0xae,0xf7,0xcf},
                                        {0x15,0xd2,0x15,0x4f},
                                        {0x16,0xa6,0x88,0x3c}
                                        };

                                      
    static const uint8_t expected[4][10] = {{0xd0,0xc9,0xe1,0xb6},
                                        {0x14,0xee,0x3f,0x63},
                                        {0xf9,0x25,0x0c,0x0c},
                                        {0xa8,0x89,0xc8,0xa6}};
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            initialArray.setValueAt(i, j, (initial_matrix[i][j]));
        }
    }



     for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            expectedResult1.setValueAt(i, j, (expected[i][j]));
        }
    }

    bool result;
    AES_mock_key_expan mockObject;
    
    mockObject.init(initialArray);

    // Test 1 - all values should be equal to one
    result = mockObject.begin_test(expectedResult1);
    REQUIRE( result == true );
    
}