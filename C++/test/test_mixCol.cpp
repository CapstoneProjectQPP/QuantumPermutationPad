#include "../include/catch2/catch_amalgamated.hpp"
#include "../include/cryptography/AES.h"
#include <iostream>

class AES_mock_mixCol : QPP::AES { 

    public:
        void init(QPP::StateArray testStateArray) {
            stateArray = testStateArray;
        }

        bool begin_test( QPP::StateArray expected) {
            // stateArray = initialArray;
            mixColumns();
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



TEST_CASE( "mixCol", "[mixCol]" ) {

    QPP::StateArray testStateArray1;
    QPP::StateArray expectedResult1;
    QPP::StateArray initialArray;
    static const uint8_t initial_matrix[4][10] = {{0xd4,0xe0,0xb8,0x1e},
                                        {0xbf,0xb4,0x41,0x27},
                                        {0x5d,0x52,0x11,0x98},
                                        {0x30,0xae,0xf1,0xe5}};
    static const uint8_t RGF_matrix[4][10] = {{0x02,0x03,0x01,0x01},
                                        {0x01,0x02,0x03,0x01},
                                        {0x01,0x01,0x02,0x03},
                                        {0x03,0x01,0x01,0x02}};
                                      
    static const uint8_t expected[4][10] = {{0x04,0xe0,0x48,0x28},
                                        {0x66,0xcb,0xf8,0x06},
                                        {0x81,0x19,0xd3,0x26},
                                        {0xe5,0x9a,0x7a,0x4c}};
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            initialArray.setValueAt(i, j, (initial_matrix[i][j]));
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            testStateArray1.setValueAt(i, j, (RGF_matrix[i][j]));
        }
    }

     for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            expectedResult1.setValueAt(i, j, (expected[i][j]));
        }
    }

    bool result;
    AES_mock_mixCol mockObject;
    
    mockObject.init(initialArray);

    // Test 1 - all values should be equal to one
    result = mockObject.begin_test(expectedResult1);
    REQUIRE( result == true );
    
}