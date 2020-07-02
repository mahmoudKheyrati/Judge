#pragma once

#include "Macros.h"
#include "Core.h"
#include <stdlib.h>
#include "stdio.h"
#include "FileHelper.h"
#include "CompileHelper.h"

struct TestCaseData {
    int testCaseNumber;
    enum Boolean isPass;
    String message;
    String output;
};
struct ResultData {
    String path;
    String fileName;
    String date;
    String score;
    String message;
    int testCaseNumber;
    struct TestCaseData *testCases;

};

String toJson(struct ResultData *data);

String strConcat(String list[], int size);

String currentTime();