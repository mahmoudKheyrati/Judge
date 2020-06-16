#include "CompileHelper.h"


/**
 * this function makes int number to char pointer or String
 *
 * @param number is the number which we wanna make it to string
 * @return is the String which we want
 */

String numberToString(int number)   {

    String stringNumber = (String)malloc(sizeof(char)*MIN_SIZE_LENGTH);

    for(int i=0; number; i++)   {

        stringNumber[i] = number%10 + '0';
        number/=10;
    }
    // at stringNumber the number is reverse so we reverse it again
    for(int i=0, j=strlen(stringNumber)-1; i<j; i++, j--){

        char tempChar = stringNumber[i];
        stringNumber[i] = stringNumber[j];
        stringNumber[j] = tempChar;
    }

    return stringNumber;
}

/**
 * this function is for executing the code which we have and send their answer to a txt file as number of test case
 *
 * @param codePath is for cmd catch the directory of code
 * @param codeName is for cmd to make exe file with gcc
 * @param inputFileName is for sending input to exe file
 * @param numberOfTestCase for numbering the answers
 */

void fileExecuter(String codePath, String codeName, String inputFileName, int numberOfTestCase) {
    // going to every directory is with cd \d
    String directoryForExe = "cd \d ";
    // the path is concatinating to the past command
    strcat(directoryForExe, codePath);
    // cmd will go to directory which we want
    system(directoryForExe);
    // for making exe file we need gcc
    String forExeMake = "gcc ";
    // the name of code must be at the end of gcc command
    strcat(forExeMake, codeName);
    // a.exe is made from the code
    system(forExeMake);
    // It gets the number of test case
    String numberAnswer = numberToString(numberOfTestCase);

    String answerName = " >Answer";
    // the number of answer is at end of it
    strcat(answerName, numberAnswer);
    // it frees the the non useful storage at numberAnswer
    free(numberAnswer);

    String forExcuteWithInput = ".\a.exe ";

    strcat(forExcuteWithInput, "<");

    strcat(forExcuteWithInput, inputFileName);

    strcat(forExcuteWithInput, answerName);
    // ./a.exe <inputFileName.txt >Answer.txt is made as we want
    strcat(forExcuteWithInput, ".txt");
    // output of a.exe is send to Answer.txt
    system(forExcuteWithInput);
}

void compile(){

}