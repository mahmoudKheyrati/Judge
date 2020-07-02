#include "CompileHelper.h"
#include "Macros.h"
#include <stdlib.h>
#include <io.h>
#include "Core.h"
#include <string.h>
#define MAX_SIZE_NAME 50
#define MAX_SIZE_LINE 1000

/**
 * making exe file with gcc in cmd
 * @param codeFilePath
 * @param codeFileName
 * @param exeFileName
 * @return if compile is made correctly return 1
 */
enum Boolean compileC(String codeFilePath, String codeFileName, String exeFileName) {
    String gccCommand;
    gccCommand = (String) malloc(sizeof(char) * MAX_SIZE_LINE);
    sprintf(gccCommand, "gcc %s\\%s -o %s\\%s", codeFilePath, codeFileName, codeFilePath, exeFileName);
    system(gccCommand);
    return isFileExist(codeFilePath, exeFileName);
}

/**
 * this function compiles java file in cmd
 * @param codeFilePath is path of java file
 * @param codeFileName is name of java file
 * @return if compiles correctly returns True else False
 */
enum Boolean compileJava(String codeFilePath, String codeFileName) {

    String codeFileNameWithJava = (String) malloc(sizeof(char) * MAX_SIZE_NAME);
    String codeFileNameWithClass = (String) malloc(sizeof(char) * MAX_SIZE_NAME);
    String command = (String) malloc(sizeof(char) * MAX_SIZE_NAME);

    sprintf(codeFileNameWithJava, "%s.java", codeFileName);
    sprintf(codeFileNameWithClass, "%s.class", codeFileName);

    sprintf(command, "javac %s\\%s", codeFilePath, codeFileNameWithJava);
    system(command);
    if (isFileExist(codeFilePath, codeFileNameWithClass)) {
        return True;
    } else {
        sprintf(command, "java -cp %s %s", codeFilePath, codeFileName);
        system(command);
        return isFileExist(codeFilePath, codeFileNameWithClass);
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
    String finalCommand = (String) malloc(sizeof(char) * MAX_SIZE_LINE);
    sprintf(finalCommand, "%s\\%s <%s\\%s >%s\\%s", exePath, exeFilename, inputPath, inputFilename, outputPath,
            outputFileName);
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
    String finalCommand = (String) malloc(sizeof(char) * MAX_SIZE_LINE);
    sprintf(finalCommand, "java %s\\%s <%s\\%s >%s\\%s", javaPath, javaFilename, inputPath, inputFilename, outputPath,
            outputFileName);
    system(finalCommand);
}