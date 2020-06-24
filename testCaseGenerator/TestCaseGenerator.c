#include "TestCaseGenerator.h"
#include <stdlib.h>

/**
 * this function first makes .exe file with c file name and path then gets the inputs as its directory and sends their
 * outputs to output file in directory which is given to function
 * @param cFilePath path of .c file which will be compiled
 * @param cFileName name of that .c file
 * @param inputsPath path of directory which input files are in there
 * @param outputsPath path of directory which we wanna send to our output files in that
 * @param numberOfInputs number of inputs which we wanna make their test cases
 * @return if all of inputs are right and function works good return True else Flase
 */
enum Boolean generate(String cFilePath, String cFileName, String inputsPath, String outputsPath) {

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

    if (!compile(cFilePath, cFileName, exeFileName)) {
        print("The .c compiling has problem\n");
        return False;
    }

    loop(i, numberOfFilesInDirectory) {
        char outputFileName[20];
        sprintf(outputFileName, "output%d.txt", i);
        runExeFile(cFilePath, exeFileName, inputsPath, nameOfInputsInDirectory[i], outputsPath, outputFileName);
    }
    ///The exe file must be deleted
    deleteFile("./",exeFileName);
    return True;
}
