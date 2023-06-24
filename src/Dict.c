#include "../include/Dict.h"


unsigned int hash(const char* key) 
{
    unsigned int hash = 0;
    while (*key) hash = (hash << 5) - hash + *key++;
    return hash % TABLE_SIZE;
}

KeyValue* pair(const char* key, const char* value) 
{
    KeyValue* pair = malloc(sizeof(*pair));
    pair->key = strdup(key);
    pair->value = strdup(value);
    pair->next = NULL;
    return pair;
}

void insert(Dict* table, const char* key, const char* value) 
{
    unsigned int idx = table->hash(key);
    KeyValue* newpair = pair(key, value);
    KeyValue** next = &(table->buckets[idx]);
    while (*next) next = &((*next)->next);
    *next = newpair;
}

char* get(Dict* table, const char* key) 
{
    unsigned int idx = table->hash(key);
    KeyValue* pair = table->buckets[idx];
    while (pair && strcmp(key, pair->key) != 0) pair = pair->next;
    return pair ? pair->value : NULL;
}

Dict createDict() 
{
    Dict table;
    memset(&table, 0, sizeof(table));
    table.hash = hash;
    table.insert = insert;
    table.get = get;
    
    return table;
}
