#include "CompileHelper.h"
#include "Macros.h"
#include <stdlib.h>
#include <io.h>
#include "Core.h"
/**
 * making exe file with gcc in cmd
 * @param codeFilePath
 * @param codeFileName
 * @param exeFileName
 * @return if compile is made correctly return 1
 */
enum Boolean compile(String codeFilePath, String codeFileName, String exeFileName) {
    char fileNameForJava[21];
    char command[50];
    int i=0;
    // this will find the format of file and compile it as its format
    while (codeFileName[i++] != '.');
    if (codeFileName[i] == 'c') {
        sprintf(command, "gcc -o %s %s\\%s", exeFileName, codeFilePath, codeFileName);
        system(command);
        return isFileExist(codeFilePath, exeFileName);
    }
    if(codeFileName[i] == 'j'){
        sprintf(command, "javac -cp .;%s %s", codeFilePath, codeFileName);
        system(command);
        sprintf(fileNameForJava, "%s.class", codeFileName);
        return isFileExist(codeFilePath, fileNameForJava);
    }
}

/**
 * run exe file and produce output based on your input file
 * you should have output directory
 * @param exePath
 * @param exeFilename
 * @param inputPath
 * @param inputFilename
 * @param outputPath
 * @param outputFileName
 */
void runExeFile(String exePath, String exeFilename,
                String inputPath, String inputFilename,
                String outputPath, String outputFileName) {

    mkdir(outputPath);
    String cd[3] = {"cd ", exePath, "/"};
    String cdCommand = strConcat(cd, 3);
    String runCommand[11] = {cdCommand, " && ", exeFilename,
                             " < ", inputPath, "/", inputFilename,
                             " > ", outputPath, "/", outputFileName};
    String finalCommand = strConcat(runCommand, 11);
    system(finalCommand);
}