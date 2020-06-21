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

    String gccCommand;
    sprintf(gccCommand, "gcc -o %s %s\\%s", exeFileName, codeFilePath, codeFileName);
    system(gccCommand);
    return isFileExist(codeFilePath, exeFileName);
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