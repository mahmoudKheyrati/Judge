#include "FileHelper.h"
#include <stdlib.h>
#include "Macros.h"
#include "stdio.h"
#include "string.h"

#define MAX_LINE_SIZE 1000
#define MAX_RESULT_SIZE MAX_LINE_SIZE*9999999

/**
 * @ifnot free the string you causes memory leak
 * @param path directory of your file
 * @param filename filename
 * @return file data as a Text
 */
String readFile(String path, String filename) {
    // create file address
    String fileAddress = malloc(sizeof(char) * MAX_LINE_SIZE);
    strcpy(fileAddress, path);
    strcat(fileAddress, "/");
    strcat(fileAddress, filename);

    FILE *file = fopen(fileAddress, "r");
    if (!file) {
        return NULL;
    }
    // read file line by line
    String result = malloc(sizeof(char) * MAX_RESULT_SIZE);
    String line = malloc(sizeof(char) * MAX_LINE_SIZE);
    while ((line = fgets(line, MAX_LINE_SIZE, file))) {
        strcat(result, line);
    }
    free(fileAddress);
    free(line);
    return result;

}

struct Output writeFile(String path, String filename, String content) {

}

String *getFilesInDirectory(String path) {

}

struct Output makeDirectories(String path) {

}

enum Boolean isFileExist(String path, String filename) {

}

enum Boolean isFolderExist(String path) {

}
