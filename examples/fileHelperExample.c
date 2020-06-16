#include "fileHelperExample.h"
#include "../core/FileHelper.h"


void readFileExample() {
    String result = readFile("./", "Makefile");
    print("%s", result);
}
void writeFileExample(){
    enum Boolean writeResult = writeFile("./","myfunctionWorksWell.txt","hi how are you\nmuliline yoho\n121212");
    if(writeResult){
        print("work correctly");
    }else{
        print("there is an error");
    }
}
