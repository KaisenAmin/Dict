#ifndef DICT_H_
#define DICT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct KeyValue
{
    char *key;
    char *value;
    struct KeyValue *next;
    struct KeyValue *previousInOrder;
    struct KeyValue *nextInOrder;
} KeyValue;

typedef struct DictItem
{
    char *key;
    char *value;
} DictItem;

typedef struct Dict
{
    KeyValue **buckets_dict;
    size_t capacity_dict;
    KeyValue *first_dict;
    KeyValue *last_dict;
    int size_field_dict;

    unsigned int (*hash_dict)(const char *key);
    void (*insert_dict)(struct Dict *self, const char *key, const char *value);
    char *(*get_dict)(struct Dict *self, const char *key);
    void (*removeKey_dict)(struct Dict *self, const char *key);
    int (*size_dict)(struct Dict *self);
    int (*exists_dict)(struct Dict *self, const char *key);
    void (*update_dict)(struct Dict *self, const char *key, const char *value);
    void (*clear_dict)(struct Dict *self);
    char **(*keys_dict)(struct Dict *self);
    char **(*values_dict)(struct Dict *self);
    DictItem *(*items_dict)(struct Dict *self);
    double (*loadFactor_dict)(struct Dict *self);
    char *(*pop_dict)(struct Dict *self, const char *key, const char *defaultVal);
    void (*print_dict)(struct Dict *self);
    bool (*isEmpty_dict)(struct Dict *self);
    DictItem *(*popItem_dict)(struct Dict *self, const char *key);
    void (*merge_dict)(struct Dict *self, struct Dict *other);
    void (*copy_dict)(struct Dict *self, struct Dict *source);
    void (*fromKeys_dict)(struct Dict *self, const char **keys, const char *value, int numKeys);
    void (*destroy_dict)(struct Dict *self);
} Dict;

Dict *createDict(void);
void destroyDict(Dict *dict);

#endif
