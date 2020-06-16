#include "FileHelper.h"
#include <stdlib.h>
#include "Macros.h"
#include "stdio.h"
#include "string.h"

#define MAX_LINE_SIZE 1000
#define MAX_RESULT_SIZE MAX_LINE_SIZE*9999999

String fileAddressMaker(String path , String filename);

/**
 * @ifnot free the string you causes memory leak
 * @param path directory of your file
 * @param filename filename
 * @return file data as a Text
 */
String readFile(String path, String filename) {
    String fileAddress = fileAddressMaker(path,filename);

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
    fclose(file);
    return result;

}

enum Boolean writeFile(String path, String filename, String content) {
    String fileAddress = fileAddressMaker(path,filename);

    FILE * file = fopen(fileAddress,"w");
    if(!file){
        return False;
    }
    fputs(content,file);
    fclose(file);
    return True;

}

String *getFilesInDirectory(String path) {

}

enum Boolean makeDirectories(String path) {

}

enum Boolean isFileExist(String path, String filename) {

}

enum Boolean isFolderExist(String path) {

}
/**
 *
 * @param path file directory
 * @param filename
 * @return concat path/filename
 */
String fileAddressMaker(String path , String filename){
    // create file address
    String fileAddress = malloc(sizeof(char) * MAX_LINE_SIZE);
    strcpy(fileAddress, path);
    strcat(fileAddress, "/");
    strcat(fileAddress, filename);
    return fileAddress;
}