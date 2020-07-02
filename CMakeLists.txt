cmake_minimum_required(VERSION 3.15)
project(judge C)

set(CMAKE_C_STANDARD 99)

add_executable(judge main.c core/FileHelper.c core/FileHelper.h core/CompileHelper.c core/CompileHelper.h core/Core.c core/Core.h judge/Judge.c judge/Judge.h testCaseGenerator/TestCaseGenerator.c testCaseGenerator/TestCaseGenerator.h cli/Cli.c cli/Cli.h core/Macros.h examples/codeConvention.c examples/codeConventions.h examples/useToJson.c examples/fileHelperExample.c examples/fileHelperExample.h examples/strConcatExample.c examples/strConcatExample.h examples/TestCaseGenExample.c examples/TestCaseGenExample.h examples/JudgeExample.c examples/JudgeExample.h examples/cliExamples.c examples/cliExamples.h examples/CompileHelperExample.c examples/CompileHelperExample.h)