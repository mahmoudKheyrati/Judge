#include "../core/Core.h"
void use(){
    struct TestCaseData case1 = {

    };
    struct TestCaseData cases[3] = {{1, True, "a message", "output"},
                                    {2, False, "a something else", "output 2"},
                                    {3, True, "a message", "output 3"},

    };
    struct ResultData data = {
            .path="path/to/file",
            .fileName="filename.c",
            .date="12/12/1212 12:12:12 gmt",
            .message="successful",
            .score="12/20",
            .testCaseNumber=3,
            .testCases=cases
    };
    String jsonData= toJson(&data);
    print("%s",jsonData);
    free(jsonData);
}