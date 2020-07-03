#include "Cli.h"

/**
 * tutorial for user
 */

void commandDescription(){
    changeConsoleColor(COLOR_WHITE);
    print("Allowed commands:\n");

    print("For entering path you can use  either relative or absolute address\n");
    changeConsoleColor(COLOR_CYAN);
    print("full described help: ");
    changeConsoleColor(COLOR_WHITE);
    print("  \"judge -help\"\n");

    changeConsoleColor(COLOR_CYAN);
    print("c compile: ");
    changeConsoleColor(COLOR_WHITE);
    print("  \"judge compile c your_code_name.c your_code_path\"\n");

    changeConsoleColor(COLOR_CYAN);
    print("java compile: ");
    changeConsoleColor(COLOR_WHITE);
    print("  \"judge compile java your_code_name.java your_code_path\"\n");

    changeConsoleColor(COLOR_CYAN);
    print("c generate: ");
    changeConsoleColor(COLOR_WHITE);
    print("  \"judge generate c your_code_name.c your_code_path your_inputs_path the_output_path\"\n");

    changeConsoleColor(COLOR_CYAN);
    print("java generate: ");
    changeConsoleColor(COLOR_WHITE);
    print("  \"judge generate java your_code_name.java your_code_path your_input_path the_output_path\"\n");

    changeConsoleColor(COLOR_CYAN);
    print("judge: ");
    changeConsoleColor(COLOR_WHITE);
    print("  \"judge judge your_code_name your_code_path your_output_path generated(answer)_output_path\"\n");
//    print("Enter the name with .c or .java extension");

    changeConsoleColor(COLOR_CYAN);
    print("show list of history files with IDs: ");
    changeConsoleColor(COLOR_WHITE);
    print("  \"judge history showlist\"\n");

    changeConsoleColor(COLOR_CYAN);
    print("show data of a specific result: ");
    changeConsoleColor(COLOR_WHITE);
    print("  \"judge history show history_file_id\"\n");
    print("Find history file id in list of history files as said above.\n");

}


void fullHelpDescription(){

    changeConsoleColor(COLOR_WHITE);
    print("This is a multipurpose judge program which will be introduced to you and how to use it:\n\n");

    changeConsoleColor(COLOR_BLOCK_BLUE);
    print("1. compile:\n\n");
    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("  Usage:\n");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n\n", "It compiles your code and make an exe file. You can compile either c program or java program.");
    changeConsoleColor(COLOR_CYAN);
    print("  How to call it:\n");
    changeConsoleColor(COLOR_YELLOW);
    print("To compile your code in c");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", " \"judge compile c your_code_name.c your_code_path\"");
    changeConsoleColor(COLOR_YELLOW);
    print("To compile your code in java");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", " \"judge compile java your_code_name.java your_code_path\"");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", "Enter the name of your code file. Then enter your code path carefully,");
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
    changeConsoleColor(COLOR_CYAN);
    print("  How to call it:\n");
    print("To generate your code in c");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", " \"judge generate c your_code_name.c your_code_path your_inputs(folder)_path the_output(folder)_path\"");
    changeConsoleColor(COLOR_YELLOW);
    print("To generate your code in java");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", " \"judge generate java your_code_name.java your_code_path your_inputs(folder)_path the_output(folder)_path\"");

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

    changeConsoleColor(COLOR_CYAN);
    print("  How to call it:\n");

    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", " \"judge judge your_code_name your_code_path your_output_path generated(answer)_output_path\"");
    print("      %25s\n", "Enter your code name (java/c). Then enter your file path. And then enter the path ");
    print("      %25s\n", "of your output directory and the path of generated output directory. Enter your paths as said before.");
    print("      %25s\n", "Then, enter the time limit for each judging by millisecond (1000ms = 1s)");
    print("      %25s\n\n\n", "Please take note that generated output directory is important to contain valid & true answers!");


    changeConsoleColor(COLOR_BLOCK_BLUE);
    print("4. see the history files:\n\n");
    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("  Usage:\n");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", "You can see the list of your result files that are saved automatically. You can also see what these ");
    print("      %25s\n", "result files contain; The name of files contains date of judging and name of your c/java file.");

    changeConsoleColor(COLOR_CYAN);
    print("  How to call it:\n");
    changeConsoleColor(COLOR_WHITE);

    changeConsoleColor(COLOR_YELLOW);
    print("  list of result files:\n");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", " \"judge history showlist\"");

    changeConsoleColor(COLOR_YELLOW);
    print("  see the result:\n");
    changeConsoleColor(COLOR_WHITE);
    print("      %25s\n", " \"judge history show history_file_id\"");
    print("      %25s\n", "you can find your 'history file id' by calling \" history showlist\" as mentioned and see the ");
    print("      %25s\n\n\n", "id of file on the left hand side of file names: id. file_name");


    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("This is the end of tutorial; Now, you are ready to use this program. call -help any time you need to.\n");
    changeConsoleColor(COLOR_WHITE);

}
