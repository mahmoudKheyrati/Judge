#include <stdio.h>
#include <stdlib.h>
#include "cli/Cli.h"
#include "core/Core.h"
#include "judge/Judge.h"
#include "examples/codeConventions.h"

int main(int argc, String argv[]) {
    loop(i, argc) {
        print("%s\n", argv[i]);
    }
    exampleStart();
    print("Hello, World! \n");
    return 0;
}
