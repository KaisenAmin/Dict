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