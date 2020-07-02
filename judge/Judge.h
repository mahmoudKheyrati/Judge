#pragma once

#include "../core/Core.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#define SIZE_OF_TEST_CASE 500
#define SIZE_OF_RESULT_DATA 100*1000
#define JUDGEMENT_RESULT_FILE_NAME "ResultOfJudgement.txt"
#define exeFileName "compiledCFile.exe"

struct ResultData *judgeAll(String outputPath, String answerPath, String filePath, String fileName, int timeLimit);