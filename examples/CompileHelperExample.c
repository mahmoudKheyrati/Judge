#include "CompileHelperExample.h"


void compileExample() {

    String exePath = "someWhere";
    String exeFilename = "something";
    String inputPath = "farfarAway";
    String inputFilename = "inputName";
    String outputPath = "someOtherPalces";
    String outputFileName = "ImOutput";
    String cFilePath = "hereIsCfile";
    String cFileName = "ImCFile";
    String javaFilePath = "thereIsJava";
    String javaFileName = "ImJavaFile";
    // If our file is on c format then we will use these functions
    if (compileC(cFilePath, cFileName, exeFilename))
        runExeFile(exePath, exeFilename, inputPath, inputFilename, outputPath, outputFileName);
    // If out file is on java format then we will use these functions
    if (compileJava(javaFilePath, javaFileName))
        // In compiling c files we could name the exe file but in java compiling the name of made program is name of file
        // with .class
        runJavaFile(javaFilePath, javaFileName, inputPath, inputFilename, outputPath, outputFileName);

}