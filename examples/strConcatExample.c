#include "strConcatExample.h"
#include "../core/Macros.h"
#include "../core/Core.h"

void strConcatExample(){
    String list[5]={"first ","second ","third ","forth ","fifth "};
    String concat= strConcat(list,5);
    print("%s",concat);
    free(concat);
}