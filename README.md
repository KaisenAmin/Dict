# Simple Dictionary Library in C

This is a simple dictionary library implemented in C. The library provides a basic hash table implementation similar to Python dictionaries.

This library provides a lot of flexibility to manage key-value pairs, including the ability to dynamically insert and retrieve data, as well as basic collision handling and a load factor for performance insights.

## Features

- Insert key-value pairs into the dictionary.
- Retrieve values based on keys.
- Chaining for collision resolution.
- Simple hash function.
- Object-oriented like approach using structs and function pointers.

* **insert_dict:** Adds a new key-value pair to the dictionary.
* **get_dict:** Retrieves a value from the dictionary using the associated key.
* **removeKey_dict:** Deletes a key-value pair from the dictionary.
* **size_dict:** this method that will return the current size of the dictionary.
* **exists_dict:** this method check a key exists or not.
* **update_dict:** this method that will update the value associated with a given key.
* **clear_dict:** this method that will remove all key/value pairs from the dictionary, effectively resetting it.
* **keys_dict:** this method that will return a list/array of all keys in the dictionary.
* **values_dict:** this method that will return a list/array of all values in the dictionary.
* **items_dict:** this method that will return a list/array of all key/value pairs as DictItem.
* **loadFactor_dict:** The load factor is a concept used in hash tables to measure how full the table is. It's calculated by dividing the number of entries in the table by the number of buckets. A higher load factor means that the table is more filled, which could lead to longer search times.
* **pop_dict:** this method removes the specified item from the dictionary.
* **print_dict:** this method print key-value pair of dictionary.
* **isEmpty_dict:** this method check a dict is empty or not.
* **popItem_dict:** this method removes the item that was last inserted into the dictionary.
* **merge_dict:** this method merge twi dict with eachOther.
* **copy_dict:** The "copy_dict" method returns a copy of the specified dictionary.
* **fromKeys_dict:** The "fromkeys_dict" method returns a dictionary with the specified keys and the specified value.

### Building

1. Clone the repository:

    ```sh
    git clone https://github.com/KaisenAmin/Dict
    ```

2. Change to the project directory:

    ```sh
    cd Dict
    ```

3. Compile the source code:

    ```sh
    gcc -std=c11 -o main .\main.c .\src\String.c .\src\Dict.c
    ./main
    ```

## Usage

Include the `Dict.h` header in your C source file.


## Note 

* **Note:** This library does not provide automatic memory management for added items. It is the responsibility of the user to manage the memory for the added key-value pairs. For example, if you add a string as a value, make sure you free the memory for that string when you no longer need it. This is particularly important when using the clear function, as it will not free the memory of the values in the dictionary.


### Examples 

1. create Dict and insert into the table.

    ```c
    #include "./include/Dict.h"

    int main(int argc, char **argv)
    {
        Dict* table = createDict();

        table->insert_dict(table, "key1", "value1");
        table->insert_dict(table, "key2", "value2");

        char *value = table->get_dict(table, "key1");

        if (value)
            printf("%s\n", value);
    }
    ```

2. use "removeKey" and "size":

    ```c
    // Create a new dictionary
    Dict* myDict = createDict();

    // Insert some key-value pairs
    myDict->insert_dict(myDict, "Key1", "Value1");
    myDict->insert_dict(myDict, "Key2", "Value2");
    myDict->insert_dict(myDict, "Key3", "Value3");

    // Print current size
    printf("Size of dictionary: %d\n", myDict->size_dict(myDict)); // Outputs: Size of dictionary: 3

    // Remove a key-value pair
    myDict->removeKey_dict(myDict, "Key1");

    // Print current size
    printf("Size of dictionary: %d\n", myDict->size_dict(myDict));
    ```

3. "exists" test element exists or not:

    ```c
    Dict* myDict = createDict();

    // Insert some key-value pairs
    myDict->insert_dict(myDict, "Key1", "Value1");
    myDict->insert_dict(myDict, "Key2", "Value2");
    myDict->insert_dict(myDict, "Key3", "Value3");

    // Print current size
    printf("Size of dictionary: %d\n", myDict->size_dict(myDict)); // Outputs: Size of dictionary: 3
    printf("Key1 exists : %d\n", myDict->exists_dict(myDict, "Key1")); // Outputs: 1
    printf("Key2 exists : %d\n", myDict->exists_dict(myDict, "Key2")); // Outputs: 0
    // Remove a key-value pair
    myDict->removeKey_dict(myDict, "Key1");

    printf("After Delete\n");

    if (myDict->exists_dict(myDict, "Key1"))
        printf("Key1 exists\n");
    else
        printf("Key1 does not exist\n");

    // Print current size
    printf("Size of dictionary: %d\n", myDict->size_dict(myDict));
    ```

4. "update" and "clear" method for updating dict or clear dictionary:

    ```c
        // Create a new dictionary
    Dict* myDict = createDict();

    // Insert some key-value pairs
    myDict->insert_dict(myDict, "Key1", "Value1");
    myDict->insert_dict(myDict, "Key2", "Value2");
    myDict->insert_dict(myDict, "Key3", "Value3");

    // Print current size
    printf("Size of dictionary: %d\n", myDict->size_dict(myDict)); // Outputs: Size of dictionary: 3
    printf("Key1 exists : %d\n", myDict->exists_dict(myDict, "Key1")); // Outputs: 1
    printf("Key2 exists : %d\n", myDict->exists_dict(myDict, "Key2")); // Outputs: 0
    // Remove a key-value pair
    myDict->removeKey_dict(myDict, "Key1");

    printf("After Delete\n");

    if (myDict->exists_dict(myDict, "Key1"))
        printf("Key1 exists\n");
    else
        printf("Key1 does not exist\n");

    // Print current size
    printf("Size of dictionary: %d\n", myDict->size_dict(myDict));

    myDict->update_dict(myDict, "Key1", "NewValue1");

    // Verify the update
    printf("%s\n", myDict->get_dict(myDict, "Key1")); // Outputs: NewValue1

    // Clear the dictionary
    myDict->clear_dict(myDict);

    // Verify the clear
    printf("%d\n", myDict->size_dict(myDict)); // Outputs: 0
    ```

5. iterate over "keys" and "values":

    ```c
        // Create a new dictionary
    Dict* myDict = createDict();

    // Insert some key-value pairs
    myDict->insert_dict(myDict, "Key1", "Value1");
    myDict->insert_dict(myDict, "Key2", "Value2");
    myDict->insert_dict(myDict, "Key3", "Value3");

    printf("Size of dictionary: %d\n", myDict->size_dict(myDict)); // Outputs: Size of dictionary: 3
   
    char** keysArray = myDict->keys_dict(myDict);
    char **valuesArray = myDict->values_dict(myDict);

    for (int i = 0; keysArray[i]; i++) 
    {
        printf("%s : %s\n", keysArray[i], valuesArray[i]);

        free(valuesArray[i]);
        free(keysArray[i]); // don't forget to free the memory!
    }

    free(keysArray);
    free(valuesArray);
    ```

6. get keys and values with items as DictItems like Python:

    ```c 
    // Create a new dictionary
    Dict* myDict = createDict();

    // Insert some key-value pairs
    myDict->insert_dict(myDict, "Key1", "Value1");
    myDict->insert_dict(myDict, "Key2", "Value2");
    myDict->insert_dict(myDict, "Key3", "Value3");

    printf("Size of dictionary: %d\n", myDict->size_dict(myDict)); // Outputs: Size of dictionary: 3
   
    DictItem* itemsArray = myDict->items_dict(myDict);

    for (int i = 0; itemsArray[i].key; i++) 
    {
        printf("%s: %s\n", itemsArray[i].key, itemsArray[i].value);
        
        free(itemsArray[i].key);
        free(itemsArray[i].value);
    }

    free(itemsArray);
    ```

7. "loadFactor" measure how full the Dict is:

    ```c 
        // Create a new dictionary
    Dict* myDict = createDict();

    // Insert some key-value pairs
    myDict->insert_dict(myDict, "Key1", "Value1");
    myDict->insert_dict(myDict, "Key2", "Value2");
    myDict->insert_dict(myDict, "Key3", "Value3");

    printf("Load factor: %f\n", myDict->loadFactor_dict(myDict));
    ```

8. "pop" remove a item with name of key:

    ```c
        // Create a new dictionary
    Dict* myDict = createDict();

    // Insert some key-value pairs
    myDict->insert_dict(myDict, "Key1", "Value1");
    myDict->insert_dict(myDict, "Key2", "Value2");
    myDict->insert_dict(myDict, "Key3", "Value3");

    printf("Size of dictionary: %d\n", myDict->size_dict(myDict)); // Outputs: Size of dictionary: 3
   
    char* poppedValue = myDict->pop_dict(myDict, "Key1", NULL);
    
    if(poppedValue != NULL)
        printf("Popped value: %s\n", poppedValue);
    else 
        printf("Key not found.\n");
   
    printf("Size of dictionary after pop: %d\n", myDict->size_dict(myDict));
    
    free(poppedValue);
    ```

9. "print" this function print dict with style:

    ```c
        // Create a new dictionary
    Dict* myDict = createDict();

    // Insert some key-value pairs
    myDict->insert_dict(myDict, "Key1", "Value1");
    myDict->insert_dict(myDict, "Key2", "Value2");
    myDict->insert_dict(myDict, "Key3", "Value3");

    myDict->print_dict(myDict);
    ```

10. "isEmpty" check method is empty or not:

    ```c
    // Create a new dictionary
    Dict* myDict = createDict();

    // Insert some key-value pairs
    myDict->insert_dict(myDict, "Key1", "Value1");
    myDict->insert_dict(myDict, "Key2", "Value2");
    myDict->insert_dict(myDict, "Key3", "Value3");

    myDict->print_dict(myDict);

    if (myDict->isEmpty_dict(myDict))
        printf("Dictionary is empty\n");
    else
        printf("Dictionary is not empty\n");
    ```

11. "popItem" like python:

    ```c
    Dict* myDict = createDict();

    myDict->insert_dict(myDict, "apple", "fruit");
    myDict->insert_dict(myDict, "carrot", "vegetable");
    myDict->insert_dict(myDict, "chicken", "meat");

    myDict->print_dict(myDict); // prints: apple: fruit, carrot: vegetable, chicken: meat

    DictItem *removedItem = myDict->popItem_dict(myDict, "carrot");
    
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

    myDict->print_dict(myDict); // prints: apple: fruit, chicken: meat
    ```

12. "merge" merge two dict with eachother:

    ```c 
    Dict* myDict = createDict();
    Dict* anotherDict = createDict();

    myDict->insert_dict(myDict, "apple", "fruit");
    myDict->insert_dict(myDict, "carrot", "vegetable");
    myDict->insert_dict(myDict, "chicken", "meat");

    anotherDict->insert_dict(anotherDict, "car", "vehicle");
    anotherDict->insert_dict(anotherDict, "cat", "animal");
    anotherDict->insert_dict(anotherDict, "pineapple", "fruit");

    printf("Before merging:\n");
    printf("MyDict:\n");
    myDict->print_dict(myDict); // prints: apple: fruit, carrot: vegetable, chicken: meat
    printf("\nAnotherDict:\n");
    anotherDict->print_dict(anotherDict); // prints: car: vehicle, cat: animal, pineapple: fruit

    myDict->merge(myDict, anotherDict);

    printf("\nAfter merging:\n");
    printf("MyDict:\n");
    myDict->print_dict(myDict); // prints: apple: fruit, carrot: vegetable, chicken: meat, car: vehicle, cat: animal, pineapple: fruit
    printf("\nAnotherDict:\n");
    anotherDict->print_dict(anotherDict);
    ```

13. "copy" create two object for returing copy of one to other one:

    ```c
    // Create new dictionary
    Dict* dict = createDict();

    // Insert key-value pairs
    dict->insert_dict(dict, "One", "1");
    dict->insert_dict(dict, "Two", "2");
    dict->insert_dict(dict, "Three", "3");

    // Print the original dictionary
    dict->print_dict(dict);

    // Create a copy of the dictionary
    Dict* copyDict = createDict();
    copyDict->copy_dict(copyDict, dict);

    // Print the copied dictionary
    copyDict->print_dict(copyDict);

    // Clean up
    dict->clear_dict(dict);
    copyDict->clear_dict(copyDict);
    
    free(dict);
    free(copyDict);
    ```

14. "fromKeys" method return dict with specefic keys and values:

    ```c
    Dict* dict = createDict();

    const char *keys[] = {"One", "Two", "Three"};
    const char *value = "Default Value";
    
    dict->fromKeys_dict(dict, keys, value, 3);

    // Print the dictionary
    dict->print_dict(dict);

    // Clean up
    dict->clear_dict(dict);
    free(dict);
    ```