#include "./include/Dict.h"

int main(void)
{
    Dict *dict = createDict();

    dict->insert_dict(dict, "apple", "fruit");
    dict->insert_dict(dict, "carrot", "vegetable");
    dict->insert_dict(dict, "chicken", "meat");
    dict->print_dict(dict);

    char *popped = dict->pop_dict(dict, "carrot", NULL);
    printf("Popped: %s\n", popped);
    free(popped);

    printf("Size: %d\n", dict->size_dict(dict));
    printf("apple exists: %d\n", dict->exists_dict(dict, "apple"));

    destroyDict(dict);
    return 0;
}
