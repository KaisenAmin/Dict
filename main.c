#include "./include/Dict.h"


int main(int argc, char **argv)
{
    // Create a new dictionary
    Dict myDict = createDict();

    // Insert some key-value pairs
    myDict.insert(&myDict, "Key1", "Value1");
    myDict.insert(&myDict, "Key2", "Value2");
    myDict.insert(&myDict, "Key3", "Value3");

    printf("Size of dictionary: %d\n", myDict.size(&myDict)); // Outputs: Size of dictionary: 3
   
    char* poppedValue = myDict.pop(&myDict, "Key1", NULL);
    
    if(poppedValue != NULL)
        printf("Popped value: %s\n", poppedValue);
    else 
        printf("Key not found.\n");
   
    printf("Size of dictionary after pop: %d\n", myDict.size(&myDict));
    
    free(poppedValue);
    
    getchar();
    return 0;  
}