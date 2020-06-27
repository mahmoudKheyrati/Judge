#include "Cli.h"
#include <windows.h>
#define MAX_FILE_NAME 1000

enum keyNameFlags{Compile = 1, GenerateTestCases, JudgeShow, Help, History, Exit};

/**
 * Changes cmd font color
 * @param colorCode
 */
void changeConsoleColor(int colorCode) {
    // color code between 0 to 255
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}

/**
 * prints the result of judge
 * @param resultData
 */
void printResult(String resultData){
    changeConsoleColor(COLOR_YELLOW);
    print("The result of judging your code is:\n");

    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("%s", resultData);
}

/**
 * if the desired dir is not available this function makes it
 * @param path
 */
void makeGuardedHistoryDir(char path[]){
    String* name = malloc(1000 * sizeof(char));

    if (isFolderExist(path) == False) {
        name[0] = path;

        //?? how to pass?
        makeDirectories(name, 1);
    }
    free(name);
}

/**
 * shows and saves your current judge histories (public and private)
 * @param data  data of judging result packed in a structure
 * @return enum that show if the function works properly
 */
int saveAndShowCurrentHistory(struct ResultData* data) {
    char choose;
    String resultString = malloc(MAX_FILE_NAME * sizeof(char));

    resultString = toJson(data);
    printResult(resultString);

    changeConsoleColor(COLOR_BLOCK_YELLOW);
    print("Do you wanna save the results? (y/n): ");
    choose = getchar();

    if (choose != 'y' && choose != 'n') {
        changeConsoleColor(COLOR_RED);
        while (choose != 'y' && choose != 'n') {
            print("Invalid answer; enter 'y' or 'n': yes or no: ");
            choose = getchar();
        }
    }
    if (choose == 'n') {
        return Exit;

    } else {
        String fileName = malloc(MAX_FILE_NAME * sizeof(char));;

        makeGuardedHistoryDir("\\.cJudge_history");
        makeGuardedHistoryDir("\\.cJudge_hidden");

        sprintf(fileName,"%s_%s", data->fileName, data->date);
        writeFile("\\.cJudge_history" , fileName, resultString);
        writeFile("\\.cJudge_hidden" ,fileName, resultString);

        free(fileName);
    }
    free(resultString);
    return True;
}

/**
 * As you enter your commands in cmd to cJudge, this function detect your arguments and track your arguments
 * @param keyArgument your main (key) argument that causes the program do sth for you
 * @param userArgument follow your argument number by  incrementing in respect of your main argument parameters
 * @return enum shows if your program worked successfully
 */
int keyDetermine(String keyArgument, int* userArgument){
    if (strcmp(keyArgument, "compile") != 0) {
        *userArgument += 3;
        return Compile;

    } else if (strcmp(keyArgument, "generate") != 0) {
        *userArgument += 4;
        return GenerateTestCases;

    } else if (strcmp(keyArgument, "judge") != 0){
        *userArgument += 3;
        return JudgeShow;

    } else if (strcmp(keyArgument, "-help") != 0){
        *userArgument += 1;
        return Help;

    } else if(strcmp(keyArgument, "exit") != 0){

        return Exit;
    }
    return False;
}




int keyCommandExecute(int keyCommandFlag,String arguments[],const int userArgument){
    struct ResultData *data;
    int validation;

    switch (keyCommandFlag) {
        case Compile:
            compile(arguments[userArgument - 2], arguments[userArgument - 1], arguments[userArgument]);
            return Exit;

        case GenerateTestCases:
            generate(arguments[userArgument - 3], arguments[userArgument - 2],
                    arguments[userArgument - 1], arguments[userArgument]);
            return Exit;

        case JudgeShow:
            data = judgeAll(arguments[userArgument - 3], arguments[userArgument - 2],
                            arguments[userArgument - 1], arguments[userArgument]);
            if (data == NULL)
                return False;

            validation = saveAndShowCurrentHistory(data);
            return validation;


        case Help:

            // a function in header
            break;

        case Exit:

            return Exit;

        default:

            return False;
    }
}

int runCli(int argc, String argv[]){
    int keyCommandFlag;
    int keyExecuteResult;
    int* userInput;
    *userInput = 0;

    print("if you are new to this program, you can enter \"cjudge -help\"\n");

    while(*userInput < argc){
        if(*userInput != 0)
            *userInput += 1;

        keyCommandFlag = keyDetermine(argv[*userInput], userInput);
        keyExecuteResult = keyCommandExecute(keyCommandFlag, argv, *userInput);

        if (keyExecuteResult == False) {
            changeConsoleColor(COLOR_BLOCK_RED);
            print(" ...The program stops here\n");
            return False;

        } else if (keyExecuteResult == Exit) {
            changeConsoleColor(COLOR_BLOCK_GREEN);
            print("Have a nice time!\n");

            return True;
        }
    }

    return True;
}