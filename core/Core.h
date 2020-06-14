#pragma once

#include "Macros.h"
#include "Core.h"
#include <stdlib.h>
#include "stdio.h"
enum Boolean{False,True};

struct TestCaseData{
    int testCaseNumber;
    enum Boolean isPass;
    String message;
    String output;
};
struct ResultData{
    String path;
    String fileName;
    String date;
    String score;
    String message;
    int testCaseNumber;
    struct TestCaseData *testCases;

};

String toJson(struct ResultData* data);