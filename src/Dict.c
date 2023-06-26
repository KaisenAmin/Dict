#include "../include/Dict.h"

/**
 * @brief Compute the hash of a key
 * 
 * @param key Key for which to compute the hash
 * @return unsigned int Computed hash of the key
 */
unsigned int hash_dict(const char *key)
{
    unsigned int hash = 0;
    while (*key)
        hash = (hash << 5) - hash + *key++;
    return hash % TABLE_SIZE;
}

/**
 * @brief Create a new key-value pair
 * 
 * @param key Key for the new pair
 * @param value Value for the new pair
 * @return KeyValue* Pointer to the new key-value pair
 */
KeyValue *pair_dict(const char *key, const char *value)
{
    KeyValue *pair = malloc(sizeof(*pair));
    pair->key = strdup(key);
    pair->value = strdup(value);
    pair->next = NULL;
    return pair;
}

/**
 * @brief Retrieve a value associated with a given key from the dictionary
 * 
 * @param table Pointer to the dictionary from which to retrieve the value
 * @param key Key for which to retrieve the value
 * @return char* Value associated with the given key, or NULL if the key does not exist
 */
char *get_dict(Dict *table, const char *key)
{
    unsigned int idx = table->hash_dict(key);
    KeyValue *pair = table->buckets_dict[idx];

    while (pair && strcmp(key, pair->key) != 0)
        pair = pair->next;

    return pair ? pair->value : NULL;
}

/**
 * @brief Insert a new key-value pair into the dictionary
 * 
 * @param table Pointer to the dictionary into which to insert the pair
 * @param key Key for the new pair
 * @param value Value for the new pair
 */
void insert_dict(Dict *table, const char *key, const char *value)
{
    unsigned int idx = table->hash_dict(key);
    KeyValue *newpair = pair(key, value);
    KeyValue **next = &(table->buckets_dict[idx]);

    while (*next)
        next = &((*next)->next);

    *next = newpair;

    table->size_field_dict++;
}

/**
 * @brief Remove a key-value pair from the dictionary
 * 
 * @param table Pointer to the dictionary from which to remove the pair
 * @param key Key for the pair to remove
 */
void removeKey_dict(Dict *table, const char *key)
{
    unsigned int idx = table->hash_dict(key);
    KeyValue **pair = &(table->buckets_dict[idx]);

    while (*pair && stringCompare(key, (*pair)->key) == 0)
        pair = &((*pair)->next);

    if (*pair)
    {
        KeyValue *temp = *pair;
        *pair = (*pair)->next;
        free(temp->key);
        free(temp->value);
        free(temp);
        table->size_field_dict--;
    }
}

/**
 * @brief Check if a key exists in the dictionary
 * 
 * @param table Pointer to the dictionary in which to check for the key
 * @param key Key for which to check
 * @return int Boolean indicating whether the key exists (non-zero) or not (zero)
 */
int exists_dict(Dict *table, const char *key)
{
    return table->get_dict(table, key) != NULL;
}

/**
 * @brief Retrieve the number of key-value pairs in the dictionary
 * 
 * @param table Pointer to the dictionary for which to retrieve the size
 * @return int Number of key-value pairs in the dictionary
 */
int size_dict(Dict *table)
{
    return table->size_field_dict;
}

/**
 * @brief Update the value associated with a given key in the dictionary, or insert a new key-value pair if the key does not exist
 * 
 * @param table Pointer to the dictionary in which to update or insert the pair
 * @param key Key for the pair to update or insert
 * @param value New value for the pair
 */
void update_dict(Dict *table, const char *key, const char *value)
{
    unsigned int idx = table->hash_dict(key);
    KeyValue *pair = table->buckets_dict[idx];
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
    table->insert_dict(table, key, value);
}

/**
 * @brief Clear all key-value pairs from the dictionary
 * 
 * @param table Pointer to the dictionary to clear
 */
void clear_dict(Dict *table)
{
    KeyValue *pair;
    KeyValue *tmp;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        pair = table->buckets_dict[i];
        while (pair)
        {
            tmp = pair;
            pair = pair->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
        }

        table->buckets_dict[i] = NULL;
    }

    // Reset size
    table->size_field_dict = 0;
}

/**
 * @brief Retrieve a list of all keys in the dictionary
 * 
 * @param table Pointer to the dictionary for which to retrieve the keys
 * @return char** List of all keys in the dictionary, terminated by a NULL pointer
 */
char **keys_dict(Dict *table)
{
    int size = table->size_dict(table);
    char **keysArray = malloc(sizeof(char *) * (size + 1)); // extra space for NULL terminator
    int index = 0;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        KeyValue *pair = table->buckets_dict[i];
        while (pair)
        {
            keysArray[index++] = strdup(pair->key);
            pair = pair->next;
        }
    }

    keysArray[index] = NULL; // NULL terminator
    return keysArray;
}

/**
 * @brief Retrieve a list of all values in the dictionary
 * 
 * @param table Pointer to the dictionary for which to retrieve the values
 * @return char** List of all values in the dictionary, terminated by a NULL pointer
 */
char **values_dict(Dict *table)
{
    int size = table->size_dict(table);
    char **valuesArray = malloc(sizeof(char *) * (size + 1)); // extra space for NULL terminator
    int index = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        KeyValue *pair = table->buckets_dict[i];
        while (pair)
        {
            valuesArray[index++] = strdup(pair->value);
            pair = pair->next;
        }
    }
    valuesArray[index] = NULL; // NULL terminator
    return valuesArray;
}

/**
 * @brief Retrieve a list of all items (key-value pairs) in the dictionary
 * 
 * @param table Pointer to the dictionary for which to retrieve the items
 * @return DictItem* List of all items in the dictionary, terminated by a NULL pointer
 */
DictItem *items_dict(Dict *table)
{
    int size = table->size_dict(table);
    DictItem *itemsArray = malloc(sizeof(DictItem) * (size + 1)); // extra space for NULL terminator
    int index = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        KeyValue *pair = table->buckets_dict[i];
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

/**
 * @brief Compute the load factor of the dictionary (number of items / table size)
 * 
 * @param table Pointer to the dictionary for which to compute the load factor
 * @return double Load factor of the dictionary
 */
double loadFactor_dict(Dict *table)
{
    int size = table->size_dict(table);
    return (double)size / TABLE_SIZE;
}

/**
 * @brief Remove a key-value pair from the dictionary and return its value, or return a default value if the key does not exist
 * 
 * @param self Pointer to the dictionary from which to remove the pair
 * @param key Key for the pair to remove
 * @param default_value Default value to return if the key does not exist
 * @return char* Value associated with the removed pair, or the default value if the key did not exist
 */
char *pop_dict(Dict *self, const char *key, const char *default_value)
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

/**
 * @brief Print all key-value pairs in the dictionary
 * 
 * @param self Pointer to the dictionary to print
 */
void print_dict(struct Dict *self)
{
    printf("Dictionary:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        KeyValue *pair = self->buckets_dict[i];
        while (pair)
        {
            printf("%s: %s\n", pair->key, pair->value);
            pair = pair->next;
        }
    }
}

/**
 * @brief Check if the dictionary is empty
 * 
 * @param self Pointer to the dictionary to check
 * @return bool Boolean indicating whether the dictionary is empty (true) or not (false)
 */
bool isEmpty_dict(Dict* self)
{
    return self->size_dict(self) == 0 ? 1 : 0;
}

/**
 * @brief Remove a key-value pair from the dictionary and return it as a DictItem, or return NULL if the key does not exist
 * 
 * @param self Pointer to the dictionary from which to remove the pair
 * @param key Key for the pair to remove
 * @return DictItem* Pointer to the removed pair as a DictItem, or NULL if the key does not exist
 */
DictItem *popItem_dict(Dict *self, const char *key)
{
    unsigned int idx = self->hash_dict(key);
    KeyValue **pair = &(self->buckets_dict[idx]);

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
        self->size_field_dict--;
        return item;
    }
    return NULL;
}

/**
 * @brief Merge two dictionaries, adding key-value pairs from the other dictionary to this one if the key does not exist
 * 
 * @param self Pointer to the dictionary into which to merge the other dictionary
 * @param other Pointer to the dictionary to merge into this one
 */
void merge_dict(Dict *self, Dict *other)
{
    char **otherKeys = other->keys_dict(other);
    int i = 0;

    while(otherKeys[i]) 
    {
        if(!self->exists_dict(self, otherKeys[i])) 
        {
            char *value = other->get_dict(other, otherKeys[i]);
            self->insert_dict(self, otherKeys[i], value);
        }

        i++;
    }
}

/**
 * @brief Copy all key-value pairs from a source dictionary to this one, overwriting any existing pairs
 * 
 * @param self Pointer to the dictionary into which to copy the pairs
 * @param source Pointer to the dictionary from which to copy the pairs
 */
void copy_dict(Dict *self, Dict *source)
{
    // Clear the current dictionary first
    self->clear_dict(self);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        KeyValue *pair = source->buckets_dict[i];
        while (pair)
        {
            self->insert_dict(self, pair->key, pair->value);
            pair = pair->next;
        }
    }
}

/**
 * @brief Insert a set of keys into the dictionary with the same value for each
 * 
 * @param self Pointer to the dictionary into which to insert the keys
 * @param keys Pointer to an array of keys to insert
 * @param value Value to associate with each key
 * @param numKeys Number of keys in the array
 */
void fromKeys_dict(Dict *self, const char **keys, const char *value, int numKeys)
{
    for (int i = 0; i < numKeys; i++)
    {
        self->insert_dict(self, keys[i], value);
    }
}

/**
 * @brief Create a new dictionary and initialize its functions
 * 
 * @return Dict* Pointer to the newly created dictionary
 */
Dict* createDict()
{
    Dict *table = malloc(sizeof(Dict));
    memset(table, 0, sizeof(Dict));

    table->hash_dict = hash_dict;
    table->insert_dict = insert_dict;
    table->get_dict = get_dict;
    table->removeKey_dict = removeKey_dict;
    table->size_dict = size_dict;
    table->exists_dict = exists_dict;
    table->update_dict = update_dict;
    table->clear_dict = clear_dict;
    table->keys_dict = keys_dict;
    table->values_dict = values_dict;
    table->items_dict = items_dict;
    table->loadFactor_dict = loadFactor_dict;
    table->pop_dict = pop_dict;
    table->size_field_dict = 0;
    table->print_dict = print_dict;
    table->isEmpty_dict = isEmpty_dict;
    table->popItem_dict = popItem_dict;
    table->merge_dict = merge_dict;
    table->copy_dict = copy_dict;
    table->fromKeys_dict = fromKeys_dict;

    return table;
}
