#include "Core.h"
#include "Macros.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include <time.h>

#define MAX_SIZE_ITEM_STRING 10000000
#define MAX_SIZE_RESULT_STRING 100000
#define MAX_CONCAT_LEN 1000000

/**
 * this function returns the current time
 * @return dateString is a String which contains the current time
 */
String currentTime(){
    String dateString = (char *)malloc(sizeof(char) * 30);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateString, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
            tm.tm_min, tm.tm_sec);
    return dateString;
}

/**
 *
 * @param data object that represent the analysis of the output data
 * @return json object that represent data
 */
String toJson(struct ResultData *data) {
    String testCases = malloc(data->testCaseNumber * sizeof(struct TestCaseData));

    for (int i = 0; i < data->testCaseNumber; ++i) {
        struct TestCaseData testCase = data->testCases[i];
        String item = (String)malloc(MAX_SIZE_ITEM_STRING * sizeof(struct TestCaseData));
        print("");
        sprintf(item, "    {\n"
                      "      \t\"testCaseNumber\": %i,\n"
                      "      \t\"isPass\": %s,\n"
                      "      \t\"message\": \"%s\",\n"
                      "    },\n", testCase.testCaseNumber, testCase.isPass ? "true" : "false",
                testCase.message);
        String a[2]={testCases,item};
        testCases= strConcat(a,2);
//        strcat(testCases, item);
        free(item);
    }
    String result = malloc(MAX_SIZE_RESULT_STRING + MAX_SIZE_ITEM_STRING * data->testCaseNumber * sizeof(struct TestCaseData));
    sprintf(result, "{\n"
                    "  \"path\": \"%s\",\n"
                    "  \"filename\": \"%s\",\n"
                    "  \"date\": \"%s\",\n"
                    "  \"score\": \"%s\",\n"
                    "  \"message\": \"%s\",\n"
                    "  \"testCases\": [\n"
                    "%s"
                    "  ]\n"
                    "}", data->path, data->fileName, data->date, data->score, data->message, testCases);

    return result;

}

/**
 * concat list of strings
 * @param list
 * @param size
 * @return concatenation of string list
 */
String strConcat(String list[], int size){
    String result= malloc(sizeof(char)*MAX_CONCAT_LEN);
    loop(i,size){
        strcat(result,list[i]);
    }
    return result;

}