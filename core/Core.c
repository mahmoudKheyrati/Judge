#include "Core.h"
#include "Macros.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"

/**
 *
 * @param data object that represent the analysis of the output data
 * @return json object that represent data
 */
String toJson(struct ResultData *data) {
    String testCases = malloc(data->testCaseNumber * sizeof(struct TestCaseData));

    for (int i = 0; i < data->testCaseNumber; ++i) {
        struct TestCaseData *testCase = data->testCases;
        String item = malloc(10000 * sizeof(struct TestCaseData));
        print("");
        sprintf(item, "    {\n"
                      "      \t\"testCaseNumber\": %i,\n"
                      "      \t\"isPass\": %s,\n"
                      "      \t\"message\": \"%s\",\n"
                      "      \t\"output\": \"%s\"\n"
                      "    },\n", testCase->testCaseNumber, testCase->isPass ? "true" : "false",
                testCase->message,
                testCase->output);
        strcat(testCases, item);
        free(item);
    }
    String result = malloc(10000000 * data->testCaseNumber * sizeof(struct TestCaseData));
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