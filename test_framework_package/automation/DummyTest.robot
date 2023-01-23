*** Settings ***
Library    backend/E2E.py

*** Variables ***


*** Keywords ***
simpleAdding
    [Arguments]    ${A}     ${B}
    ${Result} =   simpleAdding_api    ${A}    ${B}
    [Return]    ${Result}

compareStrings
    [Arguments]    ${A}     ${B}
    ${Result} =   compareStrings_api    ${A}    ${B}
    [Return]    ${Result}

encryptionAesTest
    [Arguments]    ${P}    ${A}     ${B}
    ${Result} =   encryptionAesTest_api    ${P}    ${A}    ${B}
    [Return]    ${Result}

*** Test Cases ***
SayHello
    ${num1} =   Set Variable    ${5}
    ${num2} =   Set Variable    ${3}
    ${sum} =   SimpleAdding     ${num1}     ${num2}
    Should Be Equal     ${sum}      ${8}

CompareStrings
    ${str1} =   Set Variable    Hello
    ${str2} =   Set Variable    Hello
    ${result} =   CompareStrings     ${str1}     ${str2}
    Should Be True    ${result} 
    
TestEncryptionAes
    ${text} =   Set Variable    Hello
    ${key} =   Set Variable    abcdefghijklmnop
    ${path} =   Set Variable    ../C++/bin/qpp.exe
    ${cipher} =   Set Variable    3d516280aa39e304222a712200724b09\n
    ${result} =   encryptionAesTest    ${path}    ${text}    ${key}
    BuiltIn.Log To Console    ${result}
    ${result2} =   CompareStrings     ${result}     ${cipher}
    Should Be True    ${result2} 