#pragma once

#include "Macros.h"

void runExeFile(String exePath, String exeFilename,
                String inputPath, String inputFilename,
                String outputPath, String outputFileName);

enum Boolean compileC(String codeFilePath, String codeFileName, String exeFileName);

enum Boolean compileJava(String codeFilePath, String codeFileName);

void runJavaFile(String javaPath, String javaFilename,
                 String inputPath, String inputFilename,
                 String outputPath, String outputFileName);