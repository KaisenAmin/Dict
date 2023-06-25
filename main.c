#include "./include/Dict.h"


int main(int argc, char **argv)
{
    // Create a new dictionary
    Dict myDict = createDict();

    // Insert some key-value pairs
    myDict.insert(&myDict, "Key1", "Value1");
    myDict.insert(&myDict, "Key2", "Value2");
    myDict.insert(&myDict, "Key3", "Value3");

    // Print current size
    printf("Size of dictionary: %d\n", myDict.size(&myDict)); // Outputs: Size of dictionary: 3

    // Remove a key-value pair
    myDict.removeKey(&myDict, "Key1");

    // Print current size
    printf("Size of dictionary: %d\n", myDict.size(&myDict));

    
    getchar();
    return 0;  
}