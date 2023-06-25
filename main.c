#include "./include/Dict.h"


int main(int argc, char **argv)
{
    // Create a new dictionary
    Dict myDict = createDict();

    // Insert some key-value pairs
    myDict.insert(&myDict, "Key1", "Value1");
    myDict.insert(&myDict, "Key2", "Value2");
    myDict.insert(&myDict, "Key3", "Value3");

    myDict.print(&myDict);

    if (myDict.isEmpty(&myDict))
        printf("Dictionary is empty\n");
    else
        printf("Dictionary is not empty\n");

    getchar();
    return 0;  
}