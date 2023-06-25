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
   
    DictItem* itemsArray = myDict.items(&myDict);

    for (int i = 0; itemsArray[i].key; i++) 
    {
        printf("%s: %s\n", itemsArray[i].key, itemsArray[i].value);
        
        free(itemsArray[i].key);
        free(itemsArray[i].value);
    }

    free(itemsArray);
        
    getchar();
    return 0;  
}