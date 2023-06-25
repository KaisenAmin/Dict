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
