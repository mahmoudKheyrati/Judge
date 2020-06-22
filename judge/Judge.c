#include "Judge.h"
#include <stdlib.h>

void judge(String outputPath, String answerPath, String fileName){
    struct ResultData result;
}
/**
 * the function will specifies that the output and answer are same or not
 * @param outputPath is the path of directory which output of compiledFile.exe are in there
 * @param outputName name of output files
 * @param answerPath is the path of directory which are the real answers
 * @param answerName name of answer files
 * @param answerIsValid with this we know our output is the ok or not
 * @return the details in output file even if the output is wrong
 */
String isValid(String outputPath, String outputName, String answerPath, String answerName, enum Boolean *answerIsValid){

    String outputResult = readFile(outputPath, outputName);
    String answerResult = readFile(answerPath, answerName);
    if(strcmp(outputResult, answerResult) == 0){
        *answerIsValid = True;
    }
    else{
        *answerIsValid = False;
    }
    return outputResult;
}

void saveOutput(struct ResultData * result, struct TestCaseData *testCase){
    result->testCases[result->testCaseNumber++] = *testCase;
}
void showOutput(){

}

