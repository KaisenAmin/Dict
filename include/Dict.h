#ifndef DICT_H_
#define DICT_H_


#include <stdio.h>
#include <stdlib.h>
#include "String.h"

#define TABLE_SIZE 100

typedef struct KeyValue 
{
    char* key;
    char* value;
    struct KeyValue* next;
} KeyValue;

typedef struct Dict 
{
    KeyValue* buckets[TABLE_SIZE];
    unsigned int (*hash)(const char* key);
    void (*insert)(struct Dict* self, const char* key, const char* value);
    char* (*get)(struct Dict* self, const char* key);
    void (*removeKey)(struct Dict* self, const char* key);
    int (*size)(struct Dict* self);
    int size_field;
    
} Dict;

Dict createDict();

#endif 