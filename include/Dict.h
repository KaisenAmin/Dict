#ifndef DICT_H_
#define DICT_H_


#include <stdio.h>
#include <stdlib.h>
#include "String.h"

#define TABLE_SIZE 100000

typedef struct KeyValue 
{
    char* key;
    char* value;
    struct KeyValue* next;
} KeyValue;

typedef struct DictItem
{
    char* key;
    char* value;
} DictItem;

typedef struct Dict 
{
    KeyValue* buckets[TABLE_SIZE];

    unsigned int (*hash)(const char* key);
    void (*insert)(struct Dict* self, const char* key, const char* value);
    char* (*get)(struct Dict* self, const char* key);
    void (*removeKey)(struct Dict* self, const char* key);
    int (*size)(struct Dict* self);
    int (*exists)(struct Dict* self, const char* key);
    void (*update)(struct Dict* self, const char* key, const char* value);
    void (*clear)(struct Dict* self);
    char** (*keys)(struct Dict* self);
    char** (*values)(struct Dict* self);
    DictItem* (*items)(struct Dict* self);
    double (*loadFactor)(struct Dict* self);
    char* (*pop)(struct Dict* self, const char* key, const char* defaultVal);

    int size_field;
    
} Dict;

Dict createDict();

#endif 