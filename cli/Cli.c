#include "Cli.h"
#include <windows.h>
#define MAX_FILE_NAME 1000
#define MAX_ITEM_MEMORY 20000

enum keyNameFlags{Compile = 1, GenerateTestCases, JudgeShow, Help, History, End};

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
    changeConsoleColor(COLOR_BLOCK_YELLOW);
    print("The result of judging your code is: \n");

    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("%20s", resultData);
}

/**
 * if the desired dir is not available this function create it
 * @param path
 */
void makeGuardedHistoryDir(char path[]){
    String* name = malloc(MAX_FILE_NAME * sizeof(char));

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
    String resultString;

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
        return End;

    } else {
        String fileName = malloc(MAX_FILE_NAME * sizeof(char));

        makeGuardedHistoryDir("\\.cJudge_history");
        makeGuardedHistoryDir("\\.cJudge_hidden_history");

        sprintf(fileName,"%s_%s", data->fileName, data->date);
        writeFile("\\.cJudge_history" , fileName, resultString);
        writeFile("\\.cJudge_hidden_history" ,fileName, resultString);

        free(fileName);
    }
    free(resultString);
    return True;
}

/**
 * this function shows you the name of all items in the hidden history directory.
 */
void showHistoryList(){
    int* historyItemsNumber = malloc(MAX_ITEM_MEMORY * sizeof(int));
    String* historyList = getFilesInDirectory("\\.cJudge_hidden_history", historyItemsNumber);

    changeConsoleColor(COLOR_BLOCK_YELLOW);
    print("Your total number of history files is '%d'; Your file names is as follows:\n\n", *historyItemsNumber);
    changeConsoleColor(COLOR_WHITE);

    loop(i, *historyItemsNumber){
        print(" %d.  %s\n", i, historyList[i]);
    }



    free(historyItemsNumber);
    free(historyList);
}

/**
 * as you can guess this function shows all files available in the hidden directory that contains your results history
 * @return enum that shows if the function works successfully
 */
int showHistoryFile(){
    String historyFileName = malloc(MAX_FILE_NAME * sizeof(char));

    print("Enter your file name (you can see the list of your history files, just enter 'cjudge -help'): ");
    scanf("%s", historyFileName);
    if (readFile("\\.cJudge_hidden_history", historyFileName) != NULL) {
        system("pause");
        return True;
    }
    print(" please enter your result file name correctly\n");
    return False;
}

/**
 * this function is menu that contains two options. based on user argument it acts differently
 * @param userArgument  the argument user has entered
 * @return enum that shows if the function works successfully
 */
int historyMenu(String userArgument){
    if (strcmp(userArgument, "showlist") == 0){
        showHistoryList();
        return True;

    } else if(strcmp(userArgument, "show") == 0){
        if(showHistoryFile() == True)
            return True;
        else
            return False;

    } else{
        changeConsoleColor(COLOR_RED);
        print("invalid argument entered ");
        return False;
    }
}

/**
 * As you enter your commands in cmd to cJudge, this function detect your arguments and track your sub-arguments
 * @param keyArgument your main (key) argument that causes the program do sth for you
 * @param userArgument follow your argument number by  incrementing in respect of your main argument parameters
 * @return enum shows if your program worked successfully
 */
int keyDetect(String keyArgument, int* userArgument){

    if (strcmp(keyArgument, "compile") == 0) {
        *userArgument += 3;
        return Compile;

    } else if (strcmp(keyArgument, "generate") == 0) {
        *userArgument += 4;
        return GenerateTestCases;

    } else if (strcmp(keyArgument, "judge") == 0){
        *userArgument += 3;
        return JudgeShow;

    } else if (strcmp(keyArgument, "-help") == 0){
        *userArgument += 0;
        return Help;

    } else if (strcmp(keyArgument, "history") == 0){
        *userArgument += 1;
        return History;

    } else if(strcmp(keyArgument, "end") == 0){

        return End;
    }
    return False;
}

/**
 * this function executes the main arguments the user enters; Just like a menu
 * @param keyCommandFlag  determines what this function should do
 * @param arguments  user arguments that has been entered
 * @param userArgument  number of expected user arguments
 * @return enum that shows if there is any problem
 */
int keyCommandMenu(int keyCommandFlag, String *arguments, const int userArgument){
    struct ResultData *data;
    int validation;

    switch (keyCommandFlag) {
        case Compile:
            compile(arguments[userArgument - 1], arguments[userArgument - 2], arguments[userArgument]);
            return True;

        case GenerateTestCases:
            generate(arguments[userArgument - 2], arguments[userArgument - 3],
                    arguments[userArgument - 1], arguments[userArgument]);
            return True;

        case JudgeShow:
            data = judgeAll(arguments[userArgument - 1], arguments[userArgument],
                            arguments[userArgument - 2], arguments[userArgument - 3]);
            if (data == NULL)
                return False;

            validation = saveAndShowCurrentHistory(data);
            return validation;

        case History:
            historyMenu(arguments[userArgument]);

        case Help:
            helpDescription();
            return True;

        case End:
            return End;

        default:
            changeConsoleColor(COLOR_BLOCK_RED);
            print("the argument you entered is invalid\n");
            return False;
    }
}
/**
 * main function causes executing cli
 * @param argc
 * @param argv
 * @return
 */
int runCli(int argc, String argv[]){
    int keyCommandFlag;
    int keyExecuteResult;
    int* userInput;
    *userInput = 0;

    print("if you are new to this program, you can enter \"cjudge -help\"\n");

    while(*userInput < argc){

            *userInput += 1;

        keyCommandFlag = keyDetect(argv[*userInput], userInput);
        keyExecuteResult = keyCommandMenu(keyCommandFlag, argv, *userInput);

        if (keyExecuteResult == False) {
            changeConsoleColor(COLOR_BLOCK_RED);
            print(" ...The program stops here\n");
            return False;

        } else if (keyExecuteResult == End) {
            changeConsoleColor(COLOR_BLOCK_GREEN);
            print("Have a nice time!\n");
            changeConsoleColor(COLOR_WHITE);

            return True;
        }
    }
    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("Thanks for using cjudge!\n");
    changeConsoleColor(COLOR_WHITE);

    return True;
}