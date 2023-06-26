/**
 * @file Dict.h
 * @author Amin Tahmasebi
 * @date 2023-06-26
 * @brief File containing the KeyValue, DictItem and Dict structures, as well as the creation function for a Dict.
 */


#ifndef DICT_H_
#define DICT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "String.h"

#define TABLE_SIZE 100000


/**
 * @struct KeyValue
 * @brief Structure for a key-value pair.
 *
 * This structure represents a key-value pair that will be stored in the dictionary.
 * It also contains a pointer to the next KeyValue pair, forming a linked list.
 */
typedef struct KeyValue
{
    char *key; /**< The key of the pair */
    char *value; /**< The value associated with the key */
    struct KeyValue *next; /**< Pointer to the next key-value pair */
} KeyValue;

/**
 * @struct DictItem
 * @author Amin Tahmasebi
 * @date 2023-06-26
 * @brief Structure for a dictionary item.
 *
 * This structure represents an item that can be stored in a dictionary.
 */
typedef struct DictItem
{
    char *key; /**< The key of the item */
    char *value; /**< The value associated with the key */
} DictItem;

/**
 * @struct Dict
 * @author Amin Tahmasebi
 * @date 2023-06-26
 * @brief Structure for a dictionary.
 *
 * This structure represents a dictionary, containing function pointers for various operations,
 * as well as an array of KeyValue buckets for storing data.
 */
typedef struct Dict
{
    KeyValue *buckets_dict[TABLE_SIZE]; /**< Array of pointers to key-value pairs, serving as the dictionary's buckets */

    /* Function pointers for various dictionary operations */
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
    
    int size_field_dict;

} Dict;

Dict* createDict();

#endif