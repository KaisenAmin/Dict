#ifndef DICT_H_
#define DICT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "String.h"

#define TABLE_SIZE 100000

/**
 * @file Dict.h
 * @author Amin Tahmasebi
 * @date 2023-06-26
 * @brief File containing the KeyValue, DictItem and Dict structures, as well as the creation function for a Dict.
 */

/**
 * @struct KeyValue
 * @author Amin Tahmasebi
 * @date 2023-06-26
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
    KeyValue *buckets[TABLE_SIZE]; /**< Array of pointers to key-value pairs, serving as the dictionary's buckets */

    /* Function pointers for various dictionary operations */
    unsigned int (*hash)(const char *key);
    void (*insert)(struct Dict *self, const char *key, const char *value);
    char *(*get)(struct Dict *self, const char *key);
    void (*removeKey)(struct Dict *self, const char *key);
    int (*size)(struct Dict *self);
    int (*exists)(struct Dict *self, const char *key);
    void (*update)(struct Dict *self, const char *key, const char *value);
    void (*clear)(struct Dict *self);
    char **(*keys)(struct Dict *self);
    char **(*values)(struct Dict *self);
    DictItem *(*items)(struct Dict *self);
    double (*loadFactor)(struct Dict *self);
    char *(*pop)(struct Dict *self, const char *key, const char *defaultVal);
    void (*print)(struct Dict *self);
    bool (*isEmpty)(struct Dict *self);
    DictItem *(*popItem)(struct Dict *self, const char *key);
    void (*merge)(struct Dict *self, struct Dict *other);
    void (*copy)(struct Dict *self, struct Dict *source);
    void (*fromKeys)(struct Dict *self, const char **keys, const char *value, int numKeys);
    
    int size_field;

} Dict;

/**
 * @brief Function to create and initialize a new dictionary.
 *
 * This function creates a new dictionary and initializes all its members.
 *
 * @return A pointer to the newly created dictionary.
 *
 * @author Amin Tahmasebi
 * @date 2023-06-26
 */
Dict* createDict();

#endif