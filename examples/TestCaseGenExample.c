#include "TestCaseGenExample.h"

void useGenerator() {
    // these things may be get from user
    String cFilePath = "someWhere/cFileDir";
    String cFileName = "hereIAmCFile.c";
    String resultName = "hello";
    // Input files in this path are made before even we run the program
    // the input files must be made by user
    String inputsPath = "someOtherPlace/inputs";
    String outputsPath = "someOtherPlace/outputs";
    if (generateC(cFilePath, cFileName, inputsPath, outputsPath, resultName)) {
        print("Generate was successful\n");
        // if any problem with the path or name of file or any thing else will be shown as its alarm then the
        // result of generate function is False
    }
    String javaFilePath = "otherSomeWhere";
    String javaFileName = "heyImJava.class";
    if (generateJava(javaFilePath, javaFileName, inputsPath, outputsPath)){
        print("Generate was successful\n");
    }
}