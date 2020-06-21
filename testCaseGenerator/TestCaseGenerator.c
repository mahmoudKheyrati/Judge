#include "TestCaseGenerator.h"
#include <stdlib.h>

enum Boolean generate(String cFilePath, String cFileName, String inputsPath, String outputsPath, int numberOfInputs){

    if (!isFolderExist(cFilePath)){
        print("The folder of .c file does not exist!\n");
        return False;
    }
    if (isFileExist(cFilePath, cFileName)){
        print("The .c file does not exist!\n");
        return False;
    }
    if (isFolderExist(inputsPath)){
        print("the folder of input files does not exist!");
        return False;
    }

    if(isFolderExist(outputsPath)){
        print("the folder of output files does not exist!");
        return False;
    }

    int numberOfFilesInDirectory = 0;
    String *nameOfInputsInDirectory = getFilesInDirectory(inputsPath, &numberOfFilesInDirectory);
    if(numberOfFilesInDirectory != numberOfInputs){
        print("Number of files in input directory is not same with the number which you have entered!\n");
        return False;
    }

    //enum Boolean compile(String codeFilePath, String codeFileName, String exeFileName);
    if (compile(cFilePath, cFileName, "compiledCFile")){
        print("The .c compiling has problem\n");
        return False;
    }

    //void runExeFile(String exePath, String exeFilename,
    //                String inputPath, String inputFilename,
    //                String outputPath, String outputFileName);

    loop(i, numberOfInputs){
        char outputFileName[20];
        sprintf(outputFileName, "output%d", i);
        runExeFile(cFilePath, "compiledCFile.exe", inputsPath, nameOfInputsInDirectory[i], outputsPath, outputFileName);
    }
    return True;
}
