#include "Cli.h"
#include <windows.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_FILE_NAME 500
#define MAX_PATH_CHAR 1000
#define MAX_ITEM_MEMORY 20000

struct fileId {
    String fileName;
    int id;
};

String showCurrentHistory(struct ResultData *resultData);
int saveCurrentHistory(struct ResultData *data, String resultString);
int saveHiddenHistory(String result, struct fileId *filesId, int id);
void showHistoryList(struct fileId *filesId, int historyItemsNumber);
int showHistoryFile(struct fileId *filesId);
int historyMenu(String userArgument);
int isNumberEqual(int allUserInputs, int expectedUserInputs);
int cliCompile(int expectedUserInputs, int allUserInput, String userArguments[]);
int cliGenerate(int expectedUserInputs, int allUserInputs, String userArguments[]);
int cliJudge(int expectedUserInputs, int allUserInputs, String userArguments[]);

/**
 * main function that executes all user command
 * @param argc
 * @param argv
 * @return enum that shows if the function works successfully
 */
int runCli(int argc, String argv[]) {
    int userInput = 1;


    if (argc == 1) {
        changeConsoleColor(COLOR_BLOCK_RED);
        print("Maybe you need a little help...\n");
        changeConsoleColor(COLOR_WHITE);
        commandDescription();
        return False;
    }

    if (strcmp(argv[userInput], "compile") == 0) {
        userInput += 3;
        if (cliCompile(userInput, argc, argv) == False) {

            return False;
        }

    } else if (strcmp(argv[userInput], "generate") == 0) {
        userInput += 5;
        if (cliGenerate(userInput, argc, argv) == False) {
            return False;
        }

    } else if (strcmp(argv[userInput], "judge") == 0) {
        userInput += 4;
        if (cliJudge(userInput, argc, argv) == False) {
            changeConsoleColor(COLOR_CYAN);
            print("did you use the related commands correctly?\n");
            changeConsoleColor(COLOR_WHITE);
            print(" \"judge judge your_code_name.(c or java) your_code_path your_output_path generated(answer)_output_path\"\n");


            return False;
        }

    } else if (strcmp(argv[userInput], "-help") == 0) {
        commandDescription();
        fullHelpDescription();

    } else if (strcmp(argv[userInput], "history") == 0) {
        userInput += 1;
        if (historyMenu(argv[userInput]) == False) {
            changeConsoleColor(COLOR_BLOCK_RED);
            print("\n ... the program stops here\n");
            changeConsoleColor(COLOR_WHITE);
        }

    } else {
        changeConsoleColor(COLOR_BLOCK_RED);
        print("The argument you entered is invalid. If you are new to judge, enter >> judge -help\n");
        changeConsoleColor(COLOR_WHITE);
        commandDescription();
        return False;
    }

    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("Thanks for using judge!\n");
    changeConsoleColor(COLOR_WHITE);
    return True;
}

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
String showCurrentHistory(struct ResultData *resultData) {
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
int saveCurrentHistory(struct ResultData *data, String resultString) {
    char choose;

    changeConsoleColor(COLOR_BLOCK_YELLOW);
    print("Do you wanna save the results? (y/n): ");
    choose = getchar();
    if (choose == '\n') {
        choose = getchar();
    }

    if (choose == 'n') {
        return True;

    } else if (choose == 'y') {
        String fileName = malloc(MAX_FILE_NAME * sizeof(char));
        String *directoryName = malloc(MAX_FILE_NAME * sizeof(char));

        directoryName[0] = "judge_history";
        mkdir("judge_history");
        directoryName[0] = ".judge_hidden_history";
        mkdir(".judge_hidden_history");
        struct timeval currentTime;
        gettimeofday(&currentTime, NULL);
        sprintf(fileName, "%s_%li.json", data->fileName, currentTime.tv_sec);

        if (writeFile("./judge_history", fileName, resultString)) {

            changeConsoleColor(COLOR_BLOCK_GREEN);
            print("Your file saved successfully with the name: %s in judge_history directory on %s.\n", fileName,
                  data->date);
            changeConsoleColor(COLOR_WHITE);

            writeFile(".\\.judge_hidden_history", fileName, resultString);

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
    } else {
        changeConsoleColor(COLOR_BLOCK_RED);
        print("Invalid answer.\n");
        changeConsoleColor(COLOR_WHITE);
        return False;
    }
}

/**
 * this function saves the file chosen by user in hidden directory
 * @param result : result of judging in string format
 * @param filesId : struct of all file names and their ids.
 * @param id : the id of file in showlist
 * @return enum shows if program works properly.
 */
int saveHiddenHistory(String result, struct fileId *filesId, int id) {

    String savePath = (String) malloc(MAX_PATH_CHAR);
    print("Please enter your desired path for saving this file (either relative or absolute): ");
    scanf("%s", savePath);
    if (writeFile(savePath, filesId[id - 1].fileName, result) == True) {
        changeConsoleColor(COLOR_BLOCK_GREEN);
        print("Your file saved successfully in %s.\n", savePath);
        changeConsoleColor(COLOR_WHITE);

        free(savePath);
        return True;

    } else {
        changeConsoleColor(COLOR_BLOCK_RED);
        print("Something went wrong in saving your file.\n");
        changeConsoleColor(COLOR_WHITE);
        free(savePath);
        return False;
    }
}

/**
 * this function shows you the name of all items and their IDs in the hidden history directory.
 * @param filesId  a struct* contains file name and id
 * @param historyItemsNumber number of all files in hidden history directory
 */
void showHistoryList(struct fileId *filesId, int historyItemsNumber) {
    changeConsoleColor(COLOR_BLOCK_YELLOW);
    print("Your total number of history files is '%d'; Your file names is as follows:\n\n", historyItemsNumber);
    changeConsoleColor(COLOR_WHITE);

    loop(i, historyItemsNumber) {
        print(" %d.  %s\n", filesId[i].id, filesId[i].fileName);
    }
}

/**
 * as you can guess this function shows an specific file available in the hidden directory that contains your results history
 * @param filesId  a struct* contains file name and id
 * @return enum that shows if the function works successfully
 */
int showHistoryFile(struct fileId *filesId) {
    int id;
    char choose;

    print("Enter your file id (you can see the list of your history files, just enter 'judge -help'): ");
    scanf("%d", &id);
    String result = readFile(".\\.judge_hidden_history", filesId[id - 1].fileName);
    if (result != NULL) {
        print("%s", result);

        changeConsoleColor(COLOR_BLOCK_YELLOW);
        print("Do you wanna save the this file in your desired path? (y/n): ");

        choose = getchar();
        if (choose == '\n')
            choose = getchar();


        if (choose == 'n') {
            free(result);
            return True;

        } else if (choose == 'y') {
            free(result);
            return saveHiddenHistory(result, filesId, id);

        } else {
            print("Invalid answer.");
            return False;
        }

    } else {
        print("Your id is unavailable, make sure you have entered the correct id ");
        free(result);
        return False;
    }
}

/**
 * this function is menu that contains two options. Based on user argument it acts differently
 * @param userArgument  the argument user has entered
 * @return enum that shows if the function works successfully
 */
int historyMenu(String userArgument) {
    struct fileId *filesId = (struct fileId *) malloc(MAX_ITEM_MEMORY * sizeof(struct fileId));
    int *historyItemsNumber = (int *) malloc(MAX_ITEM_MEMORY * sizeof(int));
    String *historyList = getFilesInDirectory(".\\.judge_hidden_history", historyItemsNumber);
    int valid;

    loop(i, *historyItemsNumber) {
        filesId[i].fileName = historyList[i];
        filesId[i].id = i + 1;
    }

    if (strcmp(userArgument, "showlist") == 0) {
        showHistoryList(filesId, *historyItemsNumber);

        free(historyItemsNumber);
        free(historyList);
        free(filesId);
        return True;

    } else if (strcmp(userArgument, "show") == 0) {
        valid = showHistoryFile(filesId);
        if (valid == False) {
            changeConsoleColor(COLOR_CYAN);
            print("did you use the related commands correctly?\n");
            changeConsoleColor(COLOR_WHITE);
            print(" \"judge history show history_file_id\"\n");

        }

        free(historyItemsNumber);
        free(historyList);
        free(filesId);

        return valid;

    } else {
        free(historyItemsNumber);
        free(historyList);
        free(filesId);

        changeConsoleColor(COLOR_RED);
        print("invalid argument entered ");
        changeConsoleColor(COLOR_CYAN);
        print("did you use the related commands correctly?\n");
        changeConsoleColor(COLOR_WHITE);
        print(" \"judge history showlist\"\n");
        print(" \"judge history show history_file_id\"\n");

        return False;
    }
}

/**
 * if user arguments != expected arguments for a specific command, returns False
 * @param allUserInputs
 * @param expectedUserInputs
 * @return enum shows error
 */
int isNumberEqual(int allUserInputs, int expectedUserInputs) {
    if (allUserInputs < expectedUserInputs + 1) {
        changeConsoleColor(COLOR_BLOCK_RED);
        print("The number of entered argument: %d is less than what is expected: %d\n", allUserInputs,
              expectedUserInputs + 1);
        changeConsoleColor(COLOR_WHITE);
        return False;

    } else if (allUserInputs > expectedUserInputs + 1) {
        changeConsoleColor(COLOR_BLOCK_RED);
        print("The number of entered argument: %d is more than what is expected: %d\n", allUserInputs,
              expectedUserInputs + 1);
        changeConsoleColor(COLOR_WHITE);
        return False;
    }
    return True;
}

/**
 * this function is used for compiling
 * @param expectedUserInputs
 * @param allUserInput
 * @param userArguments
 * @return enum shows if function doesn't work successfully
 */
int cliCompile(int expectedUserInputs, int allUserInput, String userArguments[]) {
    if (isNumberEqual(allUserInput, expectedUserInputs) == False) {
        changeConsoleColor(COLOR_CYAN);
        print("did you use the related commands correctly?\n");
        changeConsoleColor(COLOR_WHITE);
        print(" \"judge compile c your_code_name.c your_code_path\"\n");
        print(" \"judge compile java your_code_name.java your_code_path\"\n");

        return False;
    }

    if (strcmp(userArguments[expectedUserInputs - 2], "c") == 0) {
        String exeName = (String) malloc(MAX_FILE_NAME);

        print("Please enter the desired name for your exe file(with .exe extension): ");
        scanf("%s", exeName);

        if (compileC(userArguments[expectedUserInputs], userArguments[expectedUserInputs - 1], exeName)) {
            changeConsoleColor(COLOR_BLOCK_GREEN);
            print("Your c code is compiled successfully\n");
            free(exeName);
            changeConsoleColor(COLOR_WHITE);

        } else {
            changeConsoleColor(COLOR_BLOCK_RED);
            print(" Compiling your c code was unsuccessful ... The program stops here\n");
            changeConsoleColor(COLOR_CYAN);
            print("did you use the related commands correctly?\n");
            changeConsoleColor(COLOR_WHITE);
            print(" \"judge compile c your_code_name.c your_code_path\"\n");
            free(exeName);

            return False;
        }
    } else if (strcmp(userArguments[expectedUserInputs - 2], "java") == 0) {

        if (compileJava(userArguments[expectedUserInputs], userArguments[expectedUserInputs - 1])) {
            changeConsoleColor(COLOR_BLOCK_GREEN);
            print("Your java code is compiled successfully\n");
            changeConsoleColor(COLOR_WHITE);

        } else {
            changeConsoleColor(COLOR_BLOCK_RED);
            print(" Compiling your java code was unsuccessful ... The program stops here\n");
            changeConsoleColor(COLOR_CYAN);
            print("did you use the related commands correctly?\n");
            changeConsoleColor(COLOR_WHITE);
            print(" \"judge compile java your_code_name.java your_code_path\"\n");
            changeConsoleColor(COLOR_WHITE);
            return False;
        }

    } else {
        changeConsoleColor(COLOR_BLOCK_RED);
        print("Invalid type is entered, the program stops here.\n");
        changeConsoleColor(COLOR_CYAN);
        print("did you use the related commands correctly?\n");
        changeConsoleColor(COLOR_WHITE);
        print(" \"judge compile c your_code_name.c your_code_path\"\n");
        print(" \"judge compile java your_code_name.java your_code_path\"\n");

        return False;
    }
}

/**
 * this function is used for generating test cases
 * @param expectedUserInputs
 * @param allUserInputs
 * @param userArguments
 * @return enum shows if function doesn't work successfully
 */
int cliGenerate(int expectedUserInputs, int allUserInputs, String userArguments[]) {
    if (isNumberEqual(allUserInputs, expectedUserInputs) == False) {
        changeConsoleColor(COLOR_CYAN);
        print("did you use the related commands correctly?\n");
        changeConsoleColor(COLOR_WHITE);
        print(" \"judge generate c your_code_name.c your_code_path your_inputs_path the_output_path\"\n");
        print(" \"judge generate java your_code_name.java your_code_path your_inputs_path the_output_path\"\n");

        return False;
    }

    if (strcmp(userArguments[expectedUserInputs - 4], "c") == 0) {

        String exeName;
        exeName = strcat("Judged_", userArguments[expectedUserInputs - 3]);

        if (generateC(userArguments[expectedUserInputs - 2], userArguments[expectedUserInputs - 3],
                      userArguments[expectedUserInputs - 1], userArguments[expectedUserInputs], exeName)) {

            changeConsoleColor(COLOR_BLOCK_GREEN);
            print("c test cases are generated successfully\n");
            changeConsoleColor(COLOR_WHITE);

        } else {
            changeConsoleColor(COLOR_BLOCK_RED);
            print(" Generating c test cases was unsuccessful ... The program stops here\n");
            changeConsoleColor(COLOR_CYAN);
            print("did you use the related commands correctly?\n");
            changeConsoleColor(COLOR_WHITE);
            print(" \"judge generate c your_code_name.c your_code_path your_inputs_path the_output_path\"\n");

            return False;
        }

    } else if (strcmp(userArguments[expectedUserInputs - 4], "java") == 0) {

        if (generateJava(userArguments[expectedUserInputs - 2], userArguments[expectedUserInputs - 3],
                         userArguments[expectedUserInputs - 1], userArguments[expectedUserInputs])) {

            changeConsoleColor(COLOR_BLOCK_GREEN);
            print("Java test cases are generated successfully\n");
            changeConsoleColor(COLOR_WHITE);

        } else {
            changeConsoleColor(COLOR_BLOCK_RED);
            print(" Generating java test cases was unsuccessful ... The program stops here\n");
            changeConsoleColor(COLOR_CYAN);
            print("did you use the related commands correctly?\n");
            changeConsoleColor(COLOR_WHITE);
            print(" \"judge generate java your_code_name.java your_code_path your_inputs_path the_output_path\"\n");

            return False;
        }
    } else {
        changeConsoleColor(COLOR_BLOCK_RED);
        print("Invalid type is entered, the program stops here.\n");
        changeConsoleColor(COLOR_CYAN);
        print("did you use the related commands correctly?\n");
        changeConsoleColor(COLOR_WHITE);
        print(" \"judge generate c your_code_name.c your_code_path your_inputs_path the_output_path\"\n");
        print(" \"judge generate java your_code_name.java your_code_path your_inputs_path the_output_path\"\n");

        changeConsoleColor(COLOR_WHITE);
        return False;
    }
}

/**
 * this function is used for judging
 * @param expectedUserInputs
 * @param allUserInputs
 * @param userArguments
 * @return enum shows if function doesn't work successfully
 */
int cliJudge(int expectedUserInputs, int allUserInputs, String userArguments[]) {
    struct ResultData *data;
    int validation, timeLimit;
    String resultString;

    if (isNumberEqual(allUserInputs, expectedUserInputs) == False) {
        return False;
    }

    print("Enter the time limit for judging in ms (millisecond): ");
    scanf("%d", &timeLimit);

    data = judgeAll(userArguments[expectedUserInputs - 1], userArguments[expectedUserInputs],
                    userArguments[expectedUserInputs - 2], userArguments[expectedUserInputs - 3], timeLimit);

    if (data == NULL) {
        changeConsoleColor(COLOR_BLOCK_RED);
        // error description is in judge.c
        print(" ... The program stops here\n");
        changeConsoleColor(COLOR_WHITE);
        return False;
    }

    data->date = currentTime();
    resultString = showCurrentHistory(data);
    validation = saveCurrentHistory(data, resultString);

    if (validation == False) {
        // description written
        return False;
    }
}