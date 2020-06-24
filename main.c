#include <stdio.h>
#include <stdlib.h>
#include "cli/Cli.h"
#include "core/Core.h"
#include "judge/Judge.h"
#include "examples/codeConventions.h"
#include "examples/fileHelperExample.h"
#include "core/CompileHelper.h"

int main(int argc, String argv[]) {
    runExeFile("./runExe", "onlyTest.exe", "./in", "bed1.in", "./out", "bed1.txt");

    return 0;
}