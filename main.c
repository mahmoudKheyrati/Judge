#include <stdio.h>
#include <stdlib.h>
#include "cli/Cli.h"
#include "core/Core.h"
#include "judge/Judge.h"
#include "examples/codeConventions.h"
#include "examples/fileHelperExample.h"
#include "core/CompileHelper.h"

int main(int argc, String argv[]) {
    struct ResultData* data2 = judgeAll("./in","./out","./","aa.c",800);
    print("%s",toJson(data2));
//    struct TestCaseData case1 = {
//
//    };
//    struct TestCaseData cases[3] = {{1, True, "a message", "output"},
//                                    {2, False, "a something else", "output 2"},
//                                    {3, True, "a message", "output 3"},
//
//    };
//    struct ResultData data = {
//            .path="path/to/file",
//            .fileName="filename.c",
//            .date="12/12/1212 12:12:12 gmt",
//            .message="successful",
//            .score="12/20",
//            .testCaseNumber=3,
//            .testCases=cases
//    };
//    String jsonData= toJson(&data);
//    print("%s",jsonData);
//    free(jsonData);
//    runCli(argc,argv);
     return 0;
}