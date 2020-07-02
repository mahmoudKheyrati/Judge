#include "Judge.h"

enum Boolean isValid(String outputPath, String outputName, String answerPath, String answerName, String outputResult);

/**
 * this function initializes the ResultData at some data look like testCaseNumber or path of file and etc.
 * @param result is pointer to structure of ResultData
 * @param filePath is path of .c file
 * @param fileName is name of .c file
 * @param numberOfTestCases
 */
void initResultData(struct ResultData *result, String filePath, String fileName, int numberOfTestCases) {
    String dateString = currentTime();
    //result->testCases = (struct TestCaseData*) malloc(SIZE_OF_TEST_CASE * numberOfTestCases);
    result->testCaseNumber = numberOfTestCases;
    result->message = "Compiled Successfully";
    result->fileName = fileName;
    result->path = filePath;
    result->date = dateString;
}

/**
 * this function judges every test case
 * @param outputPath
 * @param answerPath
 * @param outputFileName
 * @param answerFileName
 * @return the testCaseData which is made in this function with its information
 */
struct TestCaseData * judge(String outputPath, String answerPath, String outputFileName, String answerFileName, int timeLimit) {
    struct timeval start;
    gettimeofday(&start, NULL);

    struct TestCaseData *pTestCase = (struct TestCaseData*) malloc(SIZE_OF_TEST_CASE);

    pTestCase->isPass = isValid(outputPath, outputFileName, answerPath, answerFileName, pTestCase->output);
    pTestCase->message = pTestCase->isPass ? "Is Valid" : "Wrong Answer";

    struct timeval stop;
    gettimeofday(&stop, NULL);
    if (stop.tv_usec - start.tv_usec > timeLimit) {
        pTestCase->message = "Time Limit";
    }
    return pTestCase;
}


/**
 * this is the Judge which makes a ResultData and an array of TestCaseData then informs validation of output and sends
 * their details to ResultData
 * @param outputPath path of directory which outputs are there
 * @param answerPath path of directory which answers are there
 * @param filePath path of .c file which is need to be at ResultData.path
 * @param fileName name of .c file
 * @param timeLimit is measure of time which must the program be run less then that time
 * @return result as ResultData
 */
struct ResultData *judgeAll(String outputPath, String answerPath, String filePath, String fileName, int timeLimit) {
    struct ResultData *result = (struct ResultData *) malloc(SIZE_OF_RESULT_DATA);

    int outputNumberFiles;
    int answerNumberFiles;
    int numberOfTestCases;
    int validNumberTestCases = 0;
    String scoreString = malloc(15* sizeof(char));

    String *filesInOutputDir = getFilesInDirectory(outputPath, &outputNumberFiles);
    String *filesInAnswerDir = getFilesInDirectory(answerPath, &answerNumberFiles);

    if (outputNumberFiles != answerNumberFiles) {
        print("There is something wrong with number of test case files in output directory and input directory!\n\n");
        return NULL;
    }

    numberOfTestCases = answerNumberFiles;
    initResultData(result, filePath, fileName, numberOfTestCases);

    result->testCases = (struct TestCaseData *) malloc(SIZE_OF_TEST_CASE * numberOfTestCases);
    struct TestCaseData *tempTestCase;
    loop(i, numberOfTestCases) {
        tempTestCase = judge(outputPath, answerPath, filesInOutputDir[i], filesInAnswerDir[i], timeLimit);
        result->testCases[i].output = tempTestCase->output;
        result->testCases[i].message = tempTestCase->message;
        result->testCases[i].isPass = tempTestCase->isPass;
        result->testCases[i].testCaseNumber = i+1;
        if (result->testCases[i].isPass) validNumberTestCases++;
    }
    sprintf(scoreString, "%d/%d", validNumberTestCases, numberOfTestCases);
    result->score = scoreString;
    free(filesInAnswerDir);
    free(filesInOutputDir);
    return result;
}

/**
 * the function will specifies that the output and answer are same or not
 * @param outputPath is the path of directory which output of compiledFile.exe are in there
 * @param outputName name of output files
 * @param answerPath is the path of directory which are the real answers
 * @param answerName name of answer files
 * @param answerIsValid with this we know our output is the ok or not
 */
enum Boolean isValid(String outputPath, String outputName, String answerPath, String answerName, String outputResult) {
    enum Boolean answerIsValid;
    outputResult = readFile(outputPath, outputName);
    String answerResult = readFile(answerPath, answerName);
    if (strcmp(outputResult, answerResult) == 0) {
        answerIsValid = True;
    } else {
        answerIsValid = False;
    }
    free(answerResult);
    return answerIsValid;
}


