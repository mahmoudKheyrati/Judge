#include "TestCaseGenerator.h"
#include <stdlib.h>

/**
 * this function first makes .exe file with c file name and path then gets the inputs as its directory and sends their
 * outputs to output file in directory which is given to function
 * @param cFilePath path of .c file which will be compiled
 * @param cFileName name of that .c file
 * @param inputsPath path of directory which input files are in there
 * @param outputsPath path of directory which we wanna send to our output files in that
 * @param resultName is name of exe file which we wanna make
 * @return if all of inputs are right and function works good return True else False
 */
enum Boolean generateC(String cFilePath, String cFileName, String inputsPath, String outputsPath, String resultName) {

    if (!isFolderExist(cFilePath)) {
        print("The folder of .c file does not exist!\n");
        return False;
    }
    if (isFileExist(cFilePath, cFileName)) {
        print("The .c file does not exist!\n");
        return False;
    }
    if (isFolderExist(inputsPath)) {
        print("the folder of input files does not exist!");
        return False;
    }

    if (isFolderExist(outputsPath)) {
        print("the folder of output files does not exist!");
        return False;
    }

    int numberOfFilesInDirectory;
    String *nameOfInputsInDirectory = getFilesInDirectory(inputsPath, &numberOfFilesInDirectory);

    if (!compileC(cFilePath, cFileName, resultName)) {
        print("The .c compiling has problem\n");
        return False;
    }

    loop(i, numberOfFilesInDirectory) {
        char outputFileName[20];
        sprintf(outputFileName, "output%d.txt", i);
        runExeFile(cFilePath, resultName, inputsPath, nameOfInputsInDirectory[i], outputsPath, outputFileName);
    }
    ///The exe file must be deleted
    deleteFile("./",resultName);
    return True;
}


/**
 * this function first makes java program with java file name and path then gets the inputs as its directory and sends
 * their outputs to output file in directory which is given to function
 * @param javaFilePath path of file which will be compiled
 * @param javaFileName name of that file
 * @param inputsPath path of directory which input files are in there
 * @param outputsPath path of directory which we wanna send to our output files in that
 * @return if all of inputs are right and function works good return True else False
 */
enum Boolean generateJava(String javaFilePath, String javaFileName, String inputsPath, String outputsPath) {

    if (!isFolderExist(javaFilePath)) {
        print("The folder of file does not exist!\n");
        return False;
    }
    if (isFileExist(javaFilePath, javaFileName)) {
        print("The file does not exist!\n");
        return False;
    }
    if (isFolderExist(inputsPath)) {
        print("the folder of input files does not exist!");
        return False;
    }

    if (isFolderExist(outputsPath)) {
        print("the folder of output files does not exist!");
        return False;
    }

    int numberOfFilesInDirectory;
    String *nameOfInputsInDirectory = getFilesInDirectory(inputsPath, &numberOfFilesInDirectory);

    if (!compileJava(javaFilePath, javaFileName)) {
        print("The compiling has problem\n");
        return False;
    }

    loop(i, numberOfFilesInDirectory) {
        char outputFileName[20];
        sprintf(outputFileName, "output%d.txt", i);
        runJavaFile(javaFilePath, javaFileName, inputsPath, nameOfInputsInDirectory[i], outputsPath, outputFileName);
    }
    ///The exe file must be deleted
    deleteFile("./",javaFileName);
    return True;
}