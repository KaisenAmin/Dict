#include "../include/Dict.h"

#include <string.h>

#define INITIAL_CAPACITY 16

static char *duplicate(const char *text)
{
    size_t size = strlen(text) + 1;
    char *copy = malloc(size);
    if (copy)
    {
        memcpy(copy, text, size);
    }
    return copy;
}

static unsigned int hash_dict(const char *key)
{
    unsigned int hash = 2166136261u;
    for (const unsigned char *c = (const unsigned char *)key; *c; c++)
    {
        hash ^= *c;
        hash *= 16777619u;
    }
    return hash;
}

static size_t bucketOf(const Dict *self, const char *key)
{
    return self->hash_dict(key) & (self->capacity_dict - 1);
}

static KeyValue *findEntry(const Dict *self, const char *key)
{
    if (!self || !key)
    {
        return NULL;
    }
    for (KeyValue *entry = self->buckets_dict[bucketOf(self, key)]; entry; entry = entry->next)
    {
        if (strcmp(entry->key, key) == 0)
        {
            return entry;
        }
    }
    return NULL;
}

static void linkBucket(Dict *self, KeyValue *entry)
{
    size_t index = bucketOf(self, entry->key);
    entry->next = self->buckets_dict[index];
    self->buckets_dict[index] = entry;
}

static void grow(Dict *self)
{
    size_t capacity = self->capacity_dict * 2;
    KeyValue **buckets = calloc(capacity, sizeof *buckets);
    if (!buckets)
    {
        return;
    }
    free(self->buckets_dict);
    self->buckets_dict = buckets;
    self->capacity_dict = capacity;
    for (KeyValue *entry = self->first_dict; entry; entry = entry->nextInOrder)
    {
        linkBucket(self, entry);
    }
}

static void unlinkEntry(Dict *self, KeyValue *entry)
{
    KeyValue **link = &self->buckets_dict[bucketOf(self, entry->key)];
    while (*link != entry)
    {
        link = &(*link)->next;
    }
    *link = entry->next;

    if (entry->previousInOrder)
    {
        entry->previousInOrder->nextInOrder = entry->nextInOrder;
    }
    else
    {
        self->first_dict = entry->nextInOrder;
    }

    if (entry->nextInOrder)
    {
        entry->nextInOrder->previousInOrder = entry->previousInOrder;
    }
    else
    {
        self->last_dict = entry->previousInOrder;
    }

    self->size_field_dict--;
}

static void freeEntry(KeyValue *entry)
{
    free(entry->key);
    free(entry->value);
    free(entry);
}

static void insert_dict(Dict *self, const char *key, const char *value)
{
    if (!self || !key || !value)
    {
        return;
    }
    char *valueCopy = duplicate(value);
    if (!valueCopy)
    {
        return;
    }

    KeyValue *existing = findEntry(self, key);
    if (existing)
    {
        free(existing->value);
        existing->value = valueCopy;
        return;
    }

    KeyValue *entry = calloc(1, sizeof *entry);
    char *keyCopy = duplicate(key);
    if (!entry || !keyCopy)
    {
        free(entry);
        free(keyCopy);
        free(valueCopy);
        return;
    }

    if ((size_t)self->size_field_dict + 1 > self->capacity_dict / 4 * 3)
    {
        grow(self);
    }

    entry->key = keyCopy;
    entry->value = valueCopy;
    entry->previousInOrder = self->last_dict;
    if (self->last_dict)
    {
        self->last_dict->nextInOrder = entry;
    }
    else
    {
        self->first_dict = entry;
    }
    self->last_dict = entry;
    linkBucket(self, entry);
    self->size_field_dict++;
}

static char *get_dict(Dict *self, const char *key)
{
    KeyValue *entry = findEntry(self, key);
    return entry ? entry->value : NULL;
}

static void removeKey_dict(Dict *self, const char *key)
{
    KeyValue *entry = findEntry(self, key);
    if (entry)
    {
        unlinkEntry(self, entry);
        freeEntry(entry);
    }
}

static int size_dict(Dict *self)
{
    return self ? self->size_field_dict : 0;
}

static int exists_dict(Dict *self, const char *key)
{
    return findEntry(self, key) != NULL;
}

static void update_dict(Dict *self, const char *key, const char *value)
{
    insert_dict(self, key, value);
}

static void clear_dict(Dict *self)
{
    if (!self)
    {
        return;
    }
    KeyValue *entry = self->first_dict;
    while (entry)
    {
        KeyValue *next = entry->nextInOrder;
        freeEntry(entry);
        entry = next;
    }
    memset(self->buckets_dict, 0, self->capacity_dict * sizeof *self->buckets_dict);
    self->first_dict = NULL;
    self->last_dict = NULL;
    self->size_field_dict = 0;
}

static char **collectStrings(Dict *self, bool keys)
{
    if (!self)
    {
        return NULL;
    }
    char **result = malloc(((size_t)self->size_field_dict + 1) * sizeof *result);
    if (!result)
    {
        return NULL;
    }
    size_t count = 0;
    for (KeyValue *entry = self->first_dict; entry; entry = entry->nextInOrder)
    {
        result[count] = duplicate(keys ? entry->key : entry->value);
        if (!result[count])
        {
            while (count > 0)
            {
                free(result[--count]);
            }
            free(result);
            return NULL;
        }
        count++;
    }
    result[count] = NULL;
    return result;
}

static char **keys_dict(Dict *self)
{
    return collectStrings(self, true);
}

static char **values_dict(Dict *self)
{
    return collectStrings(self, false);
}

static DictItem *items_dict(Dict *self)
{
    if (!self)
    {
        return NULL;
    }
    DictItem *items = calloc((size_t)self->size_field_dict + 1, sizeof *items);
    if (!items)
    {
        return NULL;
    }
    size_t count = 0;
    for (KeyValue *entry = self->first_dict; entry; entry = entry->nextInOrder, count++)
    {
        items[count].key = duplicate(entry->key);
        items[count].value = duplicate(entry->value);
        if (!items[count].key || !items[count].value)
        {
            for (size_t i = 0; i <= count; i++)
            {
                free(items[i].key);
                free(items[i].value);
            }
            free(items);
            return NULL;
        }
    }
    return items;
}

static double loadFactor_dict(Dict *self)
{
    return self ? (double)self->size_field_dict / (double)self->capacity_dict : 0.0;
}

static char *pop_dict(Dict *self, const char *key, const char *defaultVal)
{
    KeyValue *entry = findEntry(self, key);
    if (!entry)
    {
        return defaultVal ? duplicate(defaultVal) : NULL;
    }
    unlinkEntry(self, entry);
    char *value = entry->value;
    free(entry->key);
    free(entry);
    return value;
}

static void print_dict(Dict *self)
{
    for (KeyValue *entry = self ? self->first_dict : NULL; entry; entry = entry->nextInOrder)
    {
        printf("%s: %s\n", entry->key, entry->value);
    }
}

static bool isEmpty_dict(Dict *self)
{
    return size_dict(self) == 0;
}

static DictItem *popItem_dict(Dict *self, const char *key)
{
    KeyValue *entry = key ? findEntry(self, key) : (self ? self->last_dict : NULL);
    if (!entry)
    {
        return NULL;
    }
    DictItem *item = malloc(sizeof *item);
    if (!item)
    {
        return NULL;
    }
    unlinkEntry(self, entry);
    item->key = entry->key;
    item->value = entry->value;
    free(entry);
    return item;
}

static void merge_dict(Dict *self, Dict *other)
{
    if (!self || !other || self == other)
    {
        return;
    }
    for (KeyValue *entry = other->first_dict; entry; entry = entry->nextInOrder)
    {
        if (!findEntry(self, entry->key))
        {
            insert_dict(self, entry->key, entry->value);
        }
    }
}

static void copy_dict(Dict *self, Dict *source)
{
    if (!self || !source || self == source)
    {
        return;
    }
    clear_dict(self);
    for (KeyValue *entry = source->first_dict; entry; entry = entry->nextInOrder)
    {
        insert_dict(self, entry->key, entry->value);
    }
}

static void fromKeys_dict(Dict *self, const char **keys, const char *value, int numKeys)
{
    for (int i = 0; keys && i < numKeys; i++)
    {
        insert_dict(self, keys[i], value);
    }
}

void destroyDict(Dict *dict)
{
    if (!dict)
    {
        return;
    }
    clear_dict(dict);
    free(dict->buckets_dict);
    free(dict);
}

Dict *createDict(void)
{
    Dict *dict = calloc(1, sizeof *dict);
    if (!dict)
    {
        return NULL;
    }
    dict->buckets_dict = calloc(INITIAL_CAPACITY, sizeof *dict->buckets_dict);
    if (!dict->buckets_dict)
    {
        free(dict);
        return NULL;
    }
    dict->capacity_dict = INITIAL_CAPACITY;

    dict->hash_dict = hash_dict;
    dict->insert_dict = insert_dict;
    dict->get_dict = get_dict;
    dict->removeKey_dict = removeKey_dict;
    dict->size_dict = size_dict;
    dict->exists_dict = exists_dict;
    dict->update_dict = update_dict;
    dict->clear_dict = clear_dict;
    dict->keys_dict = keys_dict;
    dict->values_dict = values_dict;
    dict->items_dict = items_dict;
    dict->loadFactor_dict = loadFactor_dict;
    dict->pop_dict = pop_dict;
    dict->print_dict = print_dict;
    dict->isEmpty_dict = isEmpty_dict;
    dict->popItem_dict = popItem_dict;
    dict->merge_dict = merge_dict;
    dict->copy_dict = copy_dict;
    dict->fromKeys_dict = fromKeys_dict;
    dict->destroy_dict = destroyDict;
    return dict;
}
