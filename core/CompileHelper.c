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
enum Boolean compileC(String codeFilePath, String codeFileName, String exeFileName) {
    char command[50];
    sprintf(command, "gcc -o %s %s\\%s", exeFileName, codeFilePath, codeFileName);
    system(command);
    return isFileExist(codeFilePath, exeFileName);
}

/**
 * this function compiles java file in cmd
 * @param codeFilePath is path of java file
 * @param codeFileName is name of java file
 * @return if compiles correctly returns True else False
 */
enum Boolean compileJava(String codeFilePath, String codeFileName) {
    char fileNameForJava[21];
    char command[50];
    sprintf(command, "javac -cp .;%s %s", codeFilePath, codeFileName);
    system(command);
    sprintf(fileNameForJava, "%s.class", codeFileName);
    return isFileExist(codeFilePath, fileNameForJava);
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


/**
 * this function runs java programs
 * @param javaPath java file path
 * @param javaFilename name of java file
 * @param inputPath
 * @param inputFilename
 * @param outputPath
 * @param outputFileName
 */
void runJavaFile(String javaPath, String javaFilename,
                String inputPath, String inputFilename,
                String outputPath, String outputFileName) {

    mkdir(outputPath);
    String cd[3] = {"cd ", javaPath, "/"};
    String cdCommand = strConcat(cd, 3);
    String runCommand[11] = {cdCommand, " && ", javaFilename,
                             " < ", inputPath, "/", inputFilename,
                             " > ", outputPath, "/", outputFileName};
    String finalCommand = strConcat(runCommand, 11);
    system(finalCommand);
}