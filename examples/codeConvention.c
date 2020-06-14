#include "../core/Core.h"

void exampleStart() {
    // String type instead of char*
    String name = "mahmoud";
    // use print simply instead of printf
    print("%s\n", name);

    // swapping two variables
    String name1 = "mahmoud";
    String name2 = "reza";
    swap(name1, name2, String);
    print("%s -- %s \n\n", name1, name2);

    // basic loop start at i=0 until i < n
    loop(i, 10) {
        print("i is : %i\n", i);

    }

    // going throw all item of list without using basic for loop
    // use it when you don't need the index and only need the item
    int numbers[] = {1, 5, 3, 2, 5, 3, 23, 5};
    int sumOfNumbers = 0;
    foreach(int *item, numbers)
    {
        sumOfNumbers += *item;
    }
    print("%i\n\n", sumOfNumbers);
    //going throw list of Strings
    String names[3] = {"mahmoud", "ahmad", "reza"};
    foreach(String *item, names)
    {
        print("%s\n", *item);

    }


}