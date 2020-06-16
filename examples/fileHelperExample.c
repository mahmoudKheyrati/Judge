#include "fileHelperExample.h"
#include "../core/FileHelper.h"


void readFileExample() {
    String result = readFile("./", "Makefile");
    print("%s", result);
}
