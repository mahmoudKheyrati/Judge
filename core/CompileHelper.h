#pragma once

#include "Macros.h"

void runExeFile(String exePath, String exeFilename,
                String inputPath, String inputFilename,
                String outputPath, String outputFileName);

enum Boolean compile(String codeFilePath, String codeFileName, String exeFileName);