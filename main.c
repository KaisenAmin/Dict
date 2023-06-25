#include "./include/Dict.h"
#include <stdio.h>

int main()
{
    Dict myDict = createDict();

    myDict.insert(&myDict, "apple", "fruit");
    myDict.insert(&myDict, "carrot", "vegetable");
    myDict.insert(&myDict, "chicken", "meat");

    myDict.print(&myDict); // prints: apple: fruit, carrot: vegetable, chicken: meat

    DictItem *removedItem = myDict.popItem(&myDict, "carrot");
    
    if (removedItem)
    {
        printf("Removed key: %s, value: %s\n", removedItem->key, removedItem->value);
        free(removedItem->key);
        free(removedItem->value);
        free(removedItem);
    }
    else
    {
        printf("Item not found in the dictionary.\n");
    }

    myDict.print(&myDict); // prints: apple: fruit, chicken: meat

    return 0;
}
