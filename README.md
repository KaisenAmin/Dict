# Simple Dictionary Library in C

This is a simple dictionary library implemented in C. The library provides a basic hash table implementation similar to Python dictionaries.

## Features

- Insert key-value pairs into the dictionary.
- Retrieve values based on keys.
- Chaining for collision resolution.
- Simple hash function.
- Object-oriented like approach using structs and function pointers.

* **Insert:** Adds a new key-value pair to the dictionary.
* **Get:** Retrieves a value from the dictionary using the associated key.
* **RemoveKey:** Deletes a key-value pair from the dictionary.
* **Size:** this method that will return the current size of the dictionary.
* **Exists:** this method check a key exists or not.
* **Update:** this method that will update the value associated with a given key.
* **Clear:** this method that will remove all key/value pairs from the dictionary, effectively resetting it.
* **Keys:** this method that will return a list/array of all keys in the dictionary.
* **Values:** this method that will return a list/array of all values in the dictionary.
* **Items:** this method that will return a list/array of all key/value pairs as DictItem.


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


### Examples 

1. create Dict and insert into the table.

    ```c
    #include "./include/Dict.h"


    int main(int argc, char **argv)
    {
        Dict table = createDict();

        table.insert(&table, "key1", "value1");
        table.insert(&table, "key2", "value2");

        char* value = table.get(&table, "key1");

        if (value) 
            printf("%s\n", value);
    }
    ```

2. use "removeKey" and "size":

    ```c
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
    ```

3. "exists" test element exists or not:

    ```c
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
    ```

4. "update" and "clear" method for updating dict or clear dictionary:

    ```c
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
    ```

5. iterate over "keys" and "values":

    ```c
    // Create a new dictionary
    Dict myDict = createDict();

    // Insert some key-value pairs
    myDict.insert(&myDict, "Key1", "Value1");
    myDict.insert(&myDict, "Key2", "Value2");
    myDict.insert(&myDict, "Key3", "Value3");

    printf("Size of dictionary: %d\n", myDict.size(&myDict)); // Outputs: Size of dictionary: 3
   
    char** keysArray = myDict.keys(&myDict);
    char **valuesArray = myDict.values(&myDict);

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
    ```