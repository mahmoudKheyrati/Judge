#include "Judge.h"
#include <stdlib.h>


void
isValid(String outputPath, String outputName, String answerPath, String answerName, enum Boolean *answerIsValid, String
outputResult);

/**
 * this function initializes the ResultData at some data look like testCaseNumber or path of file and etc.
 * @param result is pointer to structure of ResultData
 * @param filePath is path of .c file
 * @param fileName is name of .c file
 * @param numberOfTestCases
 */
void initResultData(struct ResultData *result, String filePath, String fileName, int numberOfTestCases) {
    char dateString[30];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateString, "%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
            tm.tm_min, tm.tm_sec);
    result->testCaseNumber = numberOfTestCases;
    result->message = "Compiled Successfully";
    result->fileName = fileName;
    result->path = filePath;
    result->date = dateString;
}

/**
 * this is the Judge which makes a ResultData and an array of TestCaseData then informs validation of output and sends
 * their details to ResultData
 * @param outputPath path of directory which outputs are there
 * @param answerPath path of directory which answers are there
 * @param filePath path of .c file which is need to be at ResultData.path
 * @param fileName name of .c file
 * @param numberOfTestCases is the number of outputs and answers and number which the user has entered
 */
void judge(String outputPath, String answerPath, String filePath, String fileName, int numberOfTestCases) {
    struct ResultData result;
    /// Master Taheri allowed us to use variables in identifying size of arrays
    struct TestCaseData testCase[numberOfTestCases];
    enum Boolean answerIsValid;

    initResultData(&result, filePath, fileName, numberOfTestCases);

    int outputNumberFiles;
    int answerNumberFiles;
    int validNumberTestCases = 0;
    char scoreString[15];

    String *filesInOutputDir = getFilesInDirectory(outputPath, &outputNumberFiles);
    String *filesInAnswerDir = getFilesInDirectory(answerPath, &answerNumberFiles);

    if (numberOfTestCases != outputNumberFiles || numberOfTestCases != answerNumberFiles) {
        print("There is something wrong with number of test case files in output and input or number which you have entered!\n\n");
        return;
    }

    loop(i, numberOfTestCases) {
        isValid(outputPath, filesInOutputDir[i], answerPath, filesInAnswerDir[i], &answerIsValid,
                result.testCases[i].output);
        testCase[i].isPass = answerIsValid;
        testCase[i].testCaseNumber = i + 1;
        if (answerIsValid) validNumberTestCases++;
        testCase[i].message = answerIsValid ? "Is Valid" : "Wrong Answer";
    }
    result.testCases = testCase;
    sprintf(scoreString, "%d/%d", validNumberTestCases, numberOfTestCases);
    result.score = scoreString;

    String resultAtJson = toJson(&result);
    print("%s", resultAtJson);
    writeFile(outputPath, "ResultOfJudgement.txt", resultAtJson);

    free(resultAtJson);
    free(filesInAnswerDir);
    free(filesInOutputDir);
}


/**
 * the function will specifies that the output and answer are same or not and returns at pointer the output
 * @param outputPath is the path of directory which output of compiledFile.exe are in there
 * @param outputName name of output files
 * @param answerPath is the path of directory which are the real answers
 * @param answerName name of answer files
 * @param answerIsValid with this we know our output is the ok or not
 */
void isValid(String outputPath, String outputName, String answerPath, String answerName, enum Boolean *answerIsValid,
             String outputResult) {

    outputResult = readFile(outputPath, outputName);
    String answerResult = readFile(answerPath, answerName);
    if (strcmp(outputResult, answerResult) == 0) {
        *answerIsValid = True;
    } else {
        *answerIsValid = False;
    }
}


