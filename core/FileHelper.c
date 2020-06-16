#include "FileHelper.h"
#include <stdlib.h>
#include <dirent.h>
#include "Macros.h"
#include "stdio.h"
#include "string.h"

#define MAX_LINE_SIZE 1000
#define MAX_RESULT_SIZE MAX_LINE_SIZE*9999999
#define MAX_FILE_RESULT_COUNT 9999
#define MAX_FILE_NAME 1000
#define FILE_FLAG 0

String fileAddressMaker(String path, String filename);

/**
 * @ifnot free the string you causes memory leak
 * @param path directory of your file
 * @param filename filename
 * @return file data as a Text
 */
String readFile(String path, String filename) {
    String fileAddress = fileAddressMaker(path, filename);

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

/**
 *
 * @param path path/to/file
 * @param filename
 * @param content the content you want to write to the file
 * @return isSuccessful
 */
enum Boolean writeFile(String path, String filename, String content) {
    String fileAddress = fileAddressMaker(path, filename);

    FILE *file = fopen(fileAddress, "w");
    if (!file) {
        return False;
    }
    fputs(content, file);
    fclose(file);
    return True;

}

/**
 * you should free the list that you given . items first
 * @param path path/to/file
 * @param n size of files
 * @return list of file names in path
 */
String *getFilesInDirectory(String path, int *n) {
    String *result = (String *) malloc(sizeof(String) * MAX_FILE_RESULT_COUNT);
    int resSize = 0;

    struct dirent *dir;
    DIR *pDir = opendir(path);

    if (pDir) {
        while ((dir = readdir(pDir)) != NULL) {
            if (dir->d_type == FILE_FLAG) {
                String filename = malloc(sizeof(char) * strlen(dir->d_name));
                strcpy(filename, dir->d_name);
                result[resSize++] = filename;
            }
        }
        closedir(pDir);
    }
    *n = resSize;
    return result;
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
String fileAddressMaker(String path, String filename) {
    // create file address
    String fileAddress = malloc(sizeof(char) * MAX_LINE_SIZE);
    strcpy(fileAddress, path);
    strcat(fileAddress, "/");
    strcat(fileAddress, filename);
    return fileAddress;
}