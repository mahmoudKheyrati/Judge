#include "Cli.h"

/**
 * tutorial for user
 */
void helpDescription(){
    changeConsoleColor(COLOR_WHITE);
    print("This is a multipurpose judge program which will be introduced to you and how to use it:\n\n");


    changeConsoleColor(COLOR_BLOCK_BLUE);
    print("1. compile:\n\n");
    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("  Usage:\n");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n\n", "It compiles your code and make an exe file. You can compile either c program or java program.");
    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("  How to call it:\n");
    changeConsoleColor(COLOR_YELLOW);
    print("To compile your code in c");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", " \"cjudge compile c your_code_name your_code_path\"");
    changeConsoleColor(COLOR_YELLOW);
    print("To compile your code in java");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", " \"cjudge compile java your_code_name your_code_path\"");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", "Enter the name of your code file without extension. Then enter your code path carefully,");
    print("      %25s\n", "either absolute or relative address, like: ");
    print("      %25s\n", ".\\my_first_folder\\my_second_folder\\in (your input folder)");
    print("      %25s\n", "At last, enter the desired name for the compiled exe (not for compiled java file. It's name");
    print("      %25s\n\n\n", "would be saved by default name); Don't forget to enter type of your file (c/java)");

    changeConsoleColor(COLOR_BLOCK_BLUE);
    print("2. generate the test cases:\n\n");
    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("  Usage:\n");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n\n", "It generates test cases by reading your inputs and making proper output.");
    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("  How to call it:\n");
    print("To generate your code in c");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", " \"cjudge generate c your_code_name your_code_path your_inputs(folder)_path the_output(folder)_path\"");
    changeConsoleColor(COLOR_YELLOW);
    print("To generate your code in java");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", " \"cjudge generate java your_code_name your_code_path your_inputs(folder)_path the_output(folder)_path\"");

    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", "Enter the name of your code file as said in compile_section. Then enter your code path. And then");
    print("      %25s\n", "enter the paths of your input directory and the output path that generated outputs will be placed");
    print("      %25s\n\n\n", "in there. Enter your paths as said before. Don't forget to enter type of your file (c/java)");


    changeConsoleColor(COLOR_BLOCK_BLUE);
    print("3. judge your code:\n\n");
    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("  Usage:\n");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", "Here is the main work that this program does for you. Judging your program means giving the");
    print("      %25s\n", "judge your outputs. Then... judge tells you your based on your outputs and comparing them with");
    print("      %25s\n", "GENERATED outputs. So, please take note that you should 'generate test cases' before judging.");
    print("      %25s\n\n", "It also asks you whether you want to save history after showing the result of judge.");

    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("  How to call it:\n");

    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", " \"cjudge judge your_code_name your_code_path your_output_path generated(answer)_output_path\"");
    print("      %25s\n", "Enter your code name without extension. Then enter your file path. And then enter the path ");
    print("      %25s\n", "of your output directory and the path of generated output directory. Enter your paths as said before");
    print("      %25s\n\n\n", "Please take note that generated output directory is important to contain valid & true answers!");


    changeConsoleColor(COLOR_BLOCK_BLUE);
    print("4. see the history files:\n\n");
    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("  Usage:\n");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", "You can see the list of your result files that are saved automatically. You can also see what these ");
    print("      %25s\n", "result files contain; The name of files contains date of judging and name of your c/java file.");

    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("  How to call it:\n");
    changeConsoleColor(COLOR_WHITE);

    changeConsoleColor(COLOR_YELLOW);
    print("  list of result files:\n");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", " \"cjudge history showlist\"");

    changeConsoleColor(COLOR_YELLOW);
    print("  see the result:\n");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", " \"cjudge history show history_file_id\"");
    print("      %25s\n", "you can find your 'history file id' by calling \" history showlist\" as mentioned and see the ");
    print("      %25s\n\n\n", "id of file on the left hand side of file names: id. file_name");


    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("This is the end of tutorial; Now, you are ready to use this program. call -help any time you need to.\n");
    changeConsoleColor(COLOR_WHITE);

}
