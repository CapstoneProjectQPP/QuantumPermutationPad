#include "../include/catch2/catch_amalgamated.hpp"
#include "../include/cryptography/AES.h"
#include <iostream>

class AES_mock_addRoundKey : QPP::AES { 

    public:
        void init(QPP::StateArray testStateArray) {
            stateArray = testStateArray;
        }

        bool begin_test(QPP::StateArray testKeyArray, QPP::StateArray expected) {
            keySchedule.push_back(testKeyArray);
            addRoundKey(0);
            keySchedule.pop_back();
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



TEST_CASE( "addRoundKey functionality tested", "[addRoundKey]" ) {

    QPP::StateArray testKeyArray1;
    QPP::StateArray testKeyArray2;
    QPP::StateArray expectedResult1;
    QPP::StateArray expectedResult2;
    QPP::StateArray testStateArray;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(j%2 == 0) {
                testStateArray.setValueAt(i, j, 1);
            } else {
                testStateArray.setValueAt(i, j, 0);
            }
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            testKeyArray1.setValueAt(i, j, (j%2));
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            expectedResult1.setValueAt(i, j, 1);
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(j%2 == 0) {
                testKeyArray2.setValueAt(i, j, 1);
            } else {
                testKeyArray2.setValueAt(i, j, 0);
            }
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            expectedResult2.setValueAt(i, j, 0);
        }
    }

    bool result;
    AES_mock_addRoundKey mockObject;
    
    mockObject.init(testStateArray);

    // Test 1 - all values should be equal to one
    result = mockObject.begin_test(testKeyArray1, expectedResult1);
    REQUIRE( result == true );
    
    
    mockObject.init(testStateArray);

    // Test 2 - all values should be equal to zero
    result = mockObject.begin_test(testKeyArray2, expectedResult2);
    REQUIRE( result == true );
}