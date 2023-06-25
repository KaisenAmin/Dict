#include "../include/Dict.h"

unsigned int hash(const char *key)
{
    unsigned int hash = 0;
    while (*key)
        hash = (hash << 5) - hash + *key++;
    return hash % TABLE_SIZE;
}

KeyValue *pair(const char *key, const char *value)
{
    KeyValue *pair = malloc(sizeof(*pair));
    pair->key = strdup(key);
    pair->value = strdup(value);
    pair->next = NULL;
    return pair;
}

char *get(Dict *table, const char *key)
{
    unsigned int idx = table->hash(key);
    KeyValue *pair = table->buckets[idx];

    while (pair && strcmp(key, pair->key) != 0)
        pair = pair->next;

    return pair ? pair->value : NULL;
}

void insert(Dict *table, const char *key, const char *value)
{
    unsigned int idx = table->hash(key);
    KeyValue *newpair = pair(key, value);
    KeyValue **next = &(table->buckets[idx]);

    while (*next)
        next = &((*next)->next);

    *next = newpair;

    table->size_field++;
}

void removeKey(Dict *table, const char *key)
{
    unsigned int idx = table->hash(key);
    KeyValue **pair = &(table->buckets[idx]);

    while (*pair && stringCompare(key, (*pair)->key) == 0)
        pair = &((*pair)->next);

    if (*pair)
    {
        KeyValue *temp = *pair;
        *pair = (*pair)->next;
        free(temp->key);
        free(temp->value);
        free(temp);
        table->size_field--;
    }
}

int exists(Dict *table, const char *key)
{
    return table->get(table, key) != NULL;
}

int size(Dict *table)
{
    return table->size_field;
}

void update(Dict *table, const char *key, const char *value)
{
    unsigned int idx = table->hash(key);
    KeyValue *pair = table->buckets[idx];
    while (pair)
    {
        if (stringCompare(key, pair->key))
        {
            free(pair->value);
            pair->value = strdup(value);
            return;
        }
        pair = pair->next;
    }
    // If key does not exist, insert new key-value pair
    table->insert(table, key, value);
}

void clear(Dict *table)
{
    KeyValue *pair;
    KeyValue *tmp;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        pair = table->buckets[i];
        while (pair)
        {
            tmp = pair;
            pair = pair->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
        }

        table->buckets[i] = NULL;
    }

    // Reset size
    table->size_field = 0;
}

char **keys(Dict *table)
{
    int size = table->size(table);
    char **keysArray = malloc(sizeof(char *) * (size + 1)); // extra space for NULL terminator
    int index = 0;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        KeyValue *pair = table->buckets[i];
        while (pair)
        {
            keysArray[index++] = strdup(pair->key);
            pair = pair->next;
        }
    }

    keysArray[index] = NULL; // NULL terminator
    return keysArray;
}

char **values(Dict *table)
{
    int size = table->size(table);
    char **valuesArray = malloc(sizeof(char *) * (size + 1)); // extra space for NULL terminator
    int index = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        KeyValue *pair = table->buckets[i];
        while (pair)
        {
            valuesArray[index++] = strdup(pair->value);
            pair = pair->next;
        }
    }
    valuesArray[index] = NULL; // NULL terminator
    return valuesArray;
}

DictItem *items(Dict *table)
{
    int size = table->size(table);
    DictItem *itemsArray = malloc(sizeof(DictItem) * (size + 1)); // extra space for NULL terminator
    int index = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        KeyValue *pair = table->buckets[i];
        while (pair)
        {
            itemsArray[index].key = strdup(pair->key);
            itemsArray[index].value = strdup(pair->value);
            index++;
            pair = pair->next;
        }
    }
    itemsArray[index].key = NULL;   // NULL terminator
    itemsArray[index].value = NULL; // NULL terminator
    return itemsArray;
}

double loadFactor(Dict *table)
{
    int size = table->size(table);
    return (double)size / TABLE_SIZE;
}

char *pop(Dict *self, const char *key, const char *default_value)
{
    char *value = get(self, key);
    if (value)
    {
        removeKey(self, key);
        return value;
    }
    else
    {
        return (char *)default_value;
    }
}

void print(struct Dict *self)
{
    printf("Dictionary:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        KeyValue *pair = self->buckets[i];
        while (pair)
        {
            printf("%s: %s\n", pair->key, pair->value);
            pair = pair->next;
        }
    }
}

bool isEmpty(Dict* self)
{
    return self->size(self) == 0 ? 1 : 0;
}

DictItem *popItem(Dict *self, const char *key)
{
    unsigned int idx = self->hash(key);
    KeyValue **pair = &(self->buckets[idx]);

    while (*pair && strcmp(key, (*pair)->key) != 0)
        pair = &((*pair)->next);

    if (*pair)
    {
        KeyValue *temp = *pair;
        DictItem *item = malloc(sizeof(*item));
        item->key = strdup(temp->key);
        item->value = strdup(temp->value);
        *pair = (*pair)->next;
        free(temp->key);
        free(temp->value);
        free(temp);
        self->size_field--;
        return item;
    }
    return NULL;
}

void merge(Dict *self, Dict *other)
{
    char **otherKeys = other->keys(other);
    int i = 0;

    while(otherKeys[i]) 
    {
        if(!self->exists(self, otherKeys[i])) 
        {
            char *value = other->get(other, otherKeys[i]);
            self->insert(self, otherKeys[i], value);
        }

        i++;
    }
}

void copy(Dict *self, Dict *source)
{
    // Clear the current dictionary first
    self->clear(self);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        KeyValue *pair = source->buckets[i];
        while (pair)
        {
            self->insert(self, pair->key, pair->value);
            pair = pair->next;
        }
    }
}

Dict* createDict()
{
    Dict *table = malloc(sizeof(Dict));
    memset(table, 0, sizeof(Dict));

    table->hash = hash;
    table->insert = insert;
    table->get = get;
    table->removeKey = removeKey;
    table->size = size;
    table->exists = exists;
    table->update = update;
    table->clear = clear;
    table->keys = keys;
    table->values = values;
    table->items = items;
    table->loadFactor = loadFactor;
    table->pop = pop;
    table->size_field = 0;
    table->print = print;
    table->isEmpty = isEmpty;
    table->popItem = popItem;
    table->merge = merge;
    table->copy = copy;
    
    return table;
}
