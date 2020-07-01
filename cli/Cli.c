#include "Cli.h"
#include <windows.h>

#define MAX_FILE_NAME 1000
#define MAX_ITEM_MEMORY 20000

struct fileId{
    String fileName;
    int id;
};

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
 * @param resultData  struct of result
 * @return resultString  str of result
 */
String showCurrentHistory(struct ResultData* resultData){
    String resultString = toJson(resultData);

    changeConsoleColor(COLOR_BLOCK_YELLOW);
    print("The result of judging your code is: \n");

    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("%20s", resultString);
    changeConsoleColor(COLOR_WHITE);

    return resultString;
}

/**
 * saves your current judge histories (public and private)
 * @param data  data of judging result packed in a structure
 * @param resultString str of the result
 * @return enum that show if the function works properly
 */
int saveCurrentHistory(struct ResultData* data, String resultString) {
    char choose;

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
        return True;

    } else {
        String fileName = malloc(MAX_FILE_NAME * sizeof(char));
        String* directoryName = malloc(MAX_FILE_NAME * sizeof(char));

        directoryName[0] = "cJudge_history";
        makeDirectories(directoryName, 1);

        directoryName[0] = ".cJudge_hidden_history";
        makeDirectories(directoryName, 1);

        sprintf(fileName,"%s_%s.txt", data->fileName, data->date);

        if (writeFile(".\\cJudge_history" , fileName, resultString)){

            changeConsoleColor(COLOR_BLOCK_GREEN);
            print("Your file saved successfully with the name: %s in cJudge_history directory.\n", fileName);
            changeConsoleColor(COLOR_WHITE);

            //not sure about path
            writeFile(".\\.cJudge_hidden_history" ,fileName, resultString);

            free(fileName);
            free(directoryName);

            return True;

        } else {
            changeConsoleColor(COLOR_BLOCK_RED);
            print("saving your file was unsuccessful ... The program stops here\n");
            changeConsoleColor(COLOR_WHITE);

            free(fileName);
            free(directoryName);

            return False;
        }
    }
}

/**
 * this function shows you the name of all items and their IDs in the hidden history directory.
 * @param filesId  a struct* contains file name and id
 * @param historyItemsNumber number of all files in hidden history directory
 */
void showHistoryList(struct fileId* filesId, int historyItemsNumber){
    changeConsoleColor(COLOR_BLOCK_YELLOW);
    print("Your total number of history files is '%d'; Your file names is as follows:\n\n", historyItemsNumber);
    changeConsoleColor(COLOR_WHITE);

    loop(i, historyItemsNumber){
        print(" %d.  %s\n", filesId[i].id, filesId[i].fileName);
    }
}

/**
 * as you can guess this function shows an specific file available in the hidden directory that contains your results history
 * @param filesId  a struct* contains file name and id
 * @return enum that shows if the function works successfully
 */
int showHistoryFile(struct fileId* filesId){
    int id;

    print("Enter your file id (you can see the list of your history files, just enter 'cjudge -help'): ");
    scanf("%d", &id);
    if (readFile(".\\.cJudge_hidden_history", filesId[id - 1].fileName) != NULL) {
        system("pause");
        return True;
    }
    print("Your id is unavailable, make sure you have entered the correct id ");
    return False;
}

/**
 * this function is menu that contains two options. Based on user argument it acts differently
 * @param userArgument  the argument user has entered
 * @return enum that shows if the function works successfully
 */
int historyMenu(String userArgument){
    struct fileId* filesId = (struct fileId*) malloc(MAX_ITEM_MEMORY * sizeof(struct fileId));
    int* historyItemsNumber = (int*) malloc(MAX_ITEM_MEMORY * sizeof(int));
    String* historyList = getFilesInDirectory(".\\.cJudge_hidden_history", historyItemsNumber);
    int valid;

    loop(i, *historyItemsNumber){
        filesId[i].fileName = historyList[i];
        filesId[i].id = i + 1;
    }

    if (strcmp(userArgument, "showlist") == 0){
        showHistoryList(filesId, *historyItemsNumber);

        free(historyItemsNumber);
        free(historyList);
        free(filesId);
        return True;

    } else if(strcmp(userArgument, "show") == 0){
        valid = showHistoryFile(filesId);

        free(historyItemsNumber);
        free(historyList);
        free(filesId);

        if(valid == True || valid == False)
            return valid;

    } else{
        free(historyItemsNumber);
        free(historyList);
        free(filesId);

        changeConsoleColor(COLOR_RED);
        print("invalid argument entered ");
        return False;
    }
}

/**
 * main function that executes all user command
 * @param argc
 * @param argv
 * @return enum that shows if the function works successfully
 */
int runCli(int argc, String argv[]){
    int userInput = 0;
    struct ResultData *data;
    int validation;

    print("if you are new to this program, you can enter \"cjudge -help\"\n");

    while(userInput < argc){

            userInput+=1;

        if (strcmp(argv[userInput], "compile") == 0) {
            userInput += 3;
            if (compile(argv[userInput - 1], argv[userInput - 2], argv[userInput])) {
                changeConsoleColor(COLOR_BLOCK_GREEN);
                print("Your program compiled successfully\n");
                changeConsoleColor(COLOR_WHITE);

            } else {
                changeConsoleColor(COLOR_BLOCK_RED);
                print("Compiling progress was unsuccessful ... The program stops here\n");
                changeConsoleColor(COLOR_WHITE);

                return False;
            }

        } else if (strcmp(argv[userInput], "generate") == 0) {
            userInput += 4;
            if (generate(argv[userInput - 2], argv[userInput - 3], argv[userInput - 1],argv[userInput])) {
                changeConsoleColor(COLOR_BLOCK_GREEN);
                print("Test cases generated successfully\n");
                changeConsoleColor(COLOR_WHITE);

            } else {
                changeConsoleColor(COLOR_BLOCK_RED);
                print("Generating test cases was unsuccessful ... The program stops here\n");
                changeConsoleColor(COLOR_WHITE);
            }

        } else if (strcmp(argv[userInput], "judge") == 0){
            userInput += 3;

            String resultStr;

            data = judgeAll(argv[userInput - 1], argv[userInput],
                            argv[userInput - 2], argv[userInput - 3]);
            if (data == NULL) {
                changeConsoleColor(COLOR_BLOCK_RED);
                // error description is in judge.c
                print("... The program stops here\n");
                changeConsoleColor(COLOR_WHITE);

                return False;
            }
            resultStr = showCurrentHistory(data);
            validation = saveCurrentHistory(data, resultStr);

            if (validation == False)
                return False;

        } else if (strcmp(argv[userInput], "-help") == 0){
            helpDescription();
            return True;

        } else if (strcmp(argv[userInput], "history") == 0){
            userInput += 1;
            if(historyMenu(argv[userInput]) == False){
                changeConsoleColor(COLOR_BLOCK_RED);
                print("... the program stops here\n");
                changeConsoleColor(COLOR_WHITE);
            }

        }  else {
            changeConsoleColor(COLOR_BLOCK_RED);
            print("The argument you entered is invalid. Maybe you need help!\n");
            changeConsoleColor(COLOR_WHITE);
            helpDescription();

            return False;
        }
    }
    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("Thanks for using cjudge!\n");
    changeConsoleColor(COLOR_WHITE);

    return True;
}