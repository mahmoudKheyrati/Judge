#pragma once

#include "../core/Core.h"
#include "../judge/Judge.h"
#include "../testCaseGenerator/TestCaseGenerator.h"

#define COLOR_WHITE 240
#define COLOR_YELLOW 14
#define COLOR_LIGHT_BLUE 11
#define COLOR_RED 4
#define COLOR_BLOCK_GREEN 47
#define COLOR_BLOCK_YELLOW 224
#define COLOR_BLOCK_BLUE 159
#define COLOR_BLOCK_RED 79

void changeConsoleColor(int colorCode);

void helpDescription(){
    changeConsoleColor(COLOR_WHITE);
    print("This is a multipurpose judge program which will be introduced to you and how to use it:\n\n");

    print("1. compile:\n");
    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("Usage:");
    changeConsoleColor(COLOR_WHITE);
    print("%20s\n", "It compiles your code and make an exe file. You can compile either c program or java program");
    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("How to call it:");
    changeConsoleColor(COLOR_WHITE);
    print("%20s\n", "cjudge compile yourCodePath yourCodeName.c compiledFileName.exe");
    print("%20s\n", "Enter your code path carefully. Then enter the name of your code file with the exact extension of c");
    print("%20s\n\n", "or java source code. At last, enter the desired name for the compiled exe file");

    print("1. generate the testcases:\n");
    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("Usage:");
    changeConsoleColor(COLOR_WHITE);
    print("%20s\n", "");
    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("How to call it:");
    changeConsoleColor(COLOR_WHITE);
    print("%20s\n", "cjudge compile yourCodePath yourCodeName.c compiledFileName.exe");
    print("%20s\n", "Enter your code path carefully. Then enter the name of your code file with the exact extension of c");
    print("%20s\n\n", "or java source code. At last, enter the desired name for the compiled exe file");



    changeConsoleColor(COLOR_WHITE);

}
