#include "./include/Dict.h"

int main(int argc, char **argv)
{
    Dict* myDict = createDict();
    Dict* anotherDict = createDict();

    myDict->insert(myDict, "apple", "fruit");
    myDict->insert(myDict, "carrot", "vegetable");
    myDict->insert(myDict, "chicken", "meat");

    anotherDict->insert(anotherDict, "car", "vehicle");
    anotherDict->insert(anotherDict, "cat", "animal");
    anotherDict->insert(anotherDict, "pineapple", "fruit");

    printf("Before merging:\n");
    printf("MyDict:\n");
    myDict->print(myDict); // prints: apple: fruit, carrot: vegetable, chicken: meat
    printf("\nAnotherDict:\n");
    anotherDict->print(anotherDict); // prints: car: vehicle, cat: animal, pineapple: fruit

    myDict->merge(myDict, anotherDict);

    printf("\nAfter merging:\n");
    printf("MyDict:\n");
    myDict->print(myDict); // prints: apple: fruit, carrot: vegetable, chicken: meat, car: vehicle, cat: animal, pineapple: fruit
    printf("\nAnotherDict:\n");
    anotherDict->print(anotherDict);

    getchar();
    return 0;
}