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

int runCli(int argc, String argv[]);

/**
 * tutorial for user
 */
void helpDescription(){
    changeConsoleColor(COLOR_WHITE);
    print("This is a multipurpose judge program which will be introduced to you and how to use it:\n\n");

    print("1. compile:\n\n");
    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("  Usage:");
    changeConsoleColor(COLOR_WHITE);
    print("%20s\n\n", "It compiles your code and make an exe file. You can compile either c program or java program.");
    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("  How to call it:");
    changeConsoleColor(COLOR_WHITE);
    print("%20s\n", "cjudge compile your_code_name.c your_code_path compiled_file_name.exe");
    print("%20s\n", "Enter the name of your code file with the exact extension of c or java source code. Then enter");
    print("%20s\n", "your code path carefully, either absolute or relative address, like: ");
    print("%20s\n", ".\\my_first_folder\\my_second_folder\\in (your input folder)");
    print("%20s\n\n\n", "At last, enter the desired name for the compiled exe or jar file with its extension");


    print("2. generate the test cases:\n\n");
    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("  Usage:");
    changeConsoleColor(COLOR_WHITE);
    print("%20s\n\n", "It generates test cases by reading your inputs and making proper output.");
    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("  How to call it:");
    changeConsoleColor(COLOR_WHITE);
    print("%20s\n", "cjudge generate your_code_name.c your_code_path your_inputs(folder)_path the_output(folder)_path");
    print("%20s\n", "Enter the name of your code file as said in compile_section. Then enter your code path. And then");
    print("%20s\n", "enter the paths of your input directory and the output path that generated outputs will be placed");
    print("%20s\n\n\n", "in there. Enter your paths as said before ↑");

    print("3. judge your code:\n\n");
    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("  Usage:");

    changeConsoleColor(COLOR_WHITE);
    print("%20s\n", "Here is the main work that this program does for you. Judging your program means giving the");
    print("%20s\n", "judge your outputs. Then... judge tells you your based on your outputs and comparing them with");
    print("%20s\n", "GENERATED outputs. So, please take note that you should 'generate test cases' before judging. it");
    print("%20s\n\n", "also asks you whether you want to save history after showing the result of judge.");

    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("  How to call it:");

    changeConsoleColor(COLOR_WHITE);
    print("%20s\n", "cjudge judge your_code_name.c your_code_path your_output_path generated(answer)_output_path");
    print("%20s\n", "Enter your code name with c or java extension. Then enter your file path. And then enter the paths ");
    print("%20s\n", "of your output directory and the generated output directory. Enter your paths as said before");
    print("%20s\n\n\n", "Please take note that generated output directory is important to contain valid & true answers!");


    print("4. see the history files:\n\n");
    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("  Usage:");
    changeConsoleColor(COLOR_WHITE);
    print("%20s\n", "You can see the list of your result files that are saved automatically. You can also see what these ");
    print("%20s\n", "result files contain.");

    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("  How to call it:\n");
    changeConsoleColor(COLOR_WHITE);

    changeConsoleColor(COLOR_YELLOW);
    print("  list of result files:");
    changeConsoleColor(COLOR_WHITE);
    print("%20s\n", " cjudge history showlist");

    changeConsoleColor(COLOR_YELLOW);
    print("  see the result:");
    changeConsoleColor(COLOR_WHITE);
    print("%20s\n", " cjudge history show history_file_name");
    print("%20s\n\n\n", "you can find your 'history file name' by calling \" history showlist\" as mentioned");


    print("5. exit:\n\n");
    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("  Usage:");
    changeConsoleColor(COLOR_WHITE);
    print("%20s\n\n", "You can exit the program if you want to.");
    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("  How to call it:");
    changeConsoleColor(COLOR_WHITE);
    print("%20s\n\n\n", "cjudge end");

    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("this is the end of tutorial; Now, you are ready to use this program. call -help any time you need to. bye!\n");
    changeConsoleColor(COLOR_WHITE);

}
