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
    printf("Key1 exists : %d\n", myDict.exists(&myDict, "Key1")); // Outputs: 1
    printf("Key2 exists : %d\n", myDict.exists(&myDict, "Key2")); // Outputs: 0
    // Remove a key-value pair
    myDict.removeKey(&myDict, "Key1");

    printf("After Delete\n");

    if (myDict.exists(&myDict, "Key1"))
        printf("Key1 exists\n");
    else
        printf("Key1 does not exist\n");

    // Print current size
    printf("Size of dictionary: %d\n", myDict.size(&myDict));

    myDict.update(&myDict, "Key1", "NewValue1");

    // Verify the update
    printf("%s\n", myDict.get(&myDict, "Key1")); // Outputs: NewValue1

    // Clear the dictionary
    myDict.clear(&myDict);

    // Verify the clear
    printf("%d\n", myDict.size(&myDict)); // Outputs: 0

    getchar();
    return 0;  
}