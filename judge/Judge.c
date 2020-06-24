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
    char dateString[30];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateString, "%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
            tm.tm_min, tm.tm_sec);
    result = (struct ResultData *) malloc(SIZE_OF_RESULT_DATA);
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
struct TestCaseData *judge(String outputPath, String answerPath, String outputFileName, String answerFileName) {
    struct TestCaseData *TestCase = (struct TestCaseData *) malloc(SIZE_OF_TEST_CASE);
    TestCase->isPass = isValid(outputPath, outputFileName, answerPath, answerFileName, TestCase->output);
    TestCase->message = TestCase->isPass ? "Is Valid" : "Wrong Answer";
    return TestCase;
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
struct ResultData *judgeAll(String outputPath, String answerPath, String cFilePath, String cFileName) {
    struct ResultData *result;

    int outputNumberFiles;
    int answerNumberFiles;
    int numberOfTestCases;
    int validNumberTestCases = 0;
    char scoreString[15];

    String *filesInOutputDir = getFilesInDirectory(outputPath, &outputNumberFiles);
    String *filesInAnswerDir = getFilesInDirectory(answerPath, &answerNumberFiles);

    if (outputNumberFiles != answerNumberFiles) {
        print("There is something wrong with number of test case files in output directory and input directory!\n\n");
        return NULL;
    }

    numberOfTestCases = answerNumberFiles;
    initResultData(result, cFilePath, cFileName, numberOfTestCases);

    loop(i, numberOfTestCases) {
        result->testCases[i] = *judge(outputPath, answerPath, filesInOutputDir[i], filesInAnswerDir[i]);
        if (result->testCases[i].isPass) validNumberTestCases++;
    }
    sprintf(scoreString, "%d/%d", validNumberTestCases, numberOfTestCases);
    result->score = scoreString;
    /// at the output path a .txt file is made which the result of judgement is there
    String resultAtJson = toJson(result);
    writeFile(outputPath, JUDGEMENT_RESULT_FILE_NAME, resultAtJson);

    free(resultAtJson);
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


