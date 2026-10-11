#include "../include/Dict.h"

#include <string.h>

static int checks = 0;
static int failures = 0;

#define CHECK(condition) check((condition), #condition, __LINE__)

static void check(bool ok, const char *expression, int line)
{
    checks++;
    if (!ok)
    {
        failures++;
        printf("FAIL line %d: %s\n", line, expression);
    }
}

static bool equals(const char *actual, const char *expected)
{
    return actual && expected && strcmp(actual, expected) == 0;
}

static unsigned int constantHash(const char *key)
{
    (void)key;
    return 7;
}

static void freeStrings(char **strings)
{
    for (int i = 0; strings && strings[i]; i++)
    {
        free(strings[i]);
    }
    free(strings);
}

static void freeItems(DictItem *items)
{
    for (int i = 0; items && items[i].key; i++)
    {
        free(items[i].key);
        free(items[i].value);
    }
    free(items);
}

static void testInsertGetUpdate(void)
{
    Dict *dict = createDict();
    CHECK(dict != NULL);
    CHECK(dict->isEmpty_dict(dict) && dict->size_dict(dict) == 0);

    dict->insert_dict(dict, "key1", "value1");
    dict->insert_dict(dict, "key2", "value2");
    CHECK(equals(dict->get_dict(dict, "key1"), "value1"));
    CHECK(equals(dict->get_dict(dict, "key2"), "value2"));
    CHECK(dict->get_dict(dict, "missing") == NULL);
    CHECK(dict->size_dict(dict) == 2 && !dict->isEmpty_dict(dict));

    dict->insert_dict(dict, "key1", "replaced");
    CHECK(equals(dict->get_dict(dict, "key1"), "replaced") && dict->size_dict(dict) == 2);

    dict->update_dict(dict, "key2", "updated");
    dict->update_dict(dict, "key3", "inserted");
    CHECK(equals(dict->get_dict(dict, "key2"), "updated"));
    CHECK(equals(dict->get_dict(dict, "key3"), "inserted") && dict->size_dict(dict) == 3);

    char key[] = "temporary";
    dict->insert_dict(dict, key, "copied");
    key[0] = 'X';
    CHECK(equals(dict->get_dict(dict, "temporary"), "copied"));

    dict->insert_dict(dict, NULL, "ignored");
    dict->insert_dict(dict, "ignored", NULL);
    CHECK(dict->size_dict(dict) == 4 && !dict->exists_dict(dict, "ignored"));
    destroyDict(dict);
}

static void testRemoveExistsClear(void)
{
    Dict *dict = createDict();
    dict->insert_dict(dict, "Key1", "Value1");
    dict->insert_dict(dict, "Key2", "Value2");
    dict->insert_dict(dict, "Key3", "Value3");
    CHECK(dict->exists_dict(dict, "Key1") == 1 && dict->exists_dict(dict, "Key4") == 0);

    dict->removeKey_dict(dict, "Key1");
    CHECK(!dict->exists_dict(dict, "Key1") && dict->size_dict(dict) == 2);
    dict->removeKey_dict(dict, "Key1");
    dict->removeKey_dict(dict, "nothing");
    CHECK(dict->size_dict(dict) == 2);
    CHECK(equals(dict->get_dict(dict, "Key2"), "Value2") && equals(dict->get_dict(dict, "Key3"), "Value3"));

    dict->clear_dict(dict);
    CHECK(dict->size_dict(dict) == 0 && dict->isEmpty_dict(dict) && dict->get_dict(dict, "Key2") == NULL);
    dict->insert_dict(dict, "again", "works");
    CHECK(equals(dict->get_dict(dict, "again"), "works") && dict->size_dict(dict) == 1);
    dict->destroy_dict(dict);
}

static void testOrderedViews(void)
{
    Dict *dict = createDict();
    dict->insert_dict(dict, "apple", "fruit");
    dict->insert_dict(dict, "carrot", "vegetable");
    dict->insert_dict(dict, "chicken", "meat");
    dict->insert_dict(dict, "apple", "red fruit");

    char **keys = dict->keys_dict(dict);
    char **values = dict->values_dict(dict);
    CHECK(keys && equals(keys[0], "apple") && equals(keys[1], "carrot") && equals(keys[2], "chicken") && !keys[3]);
    CHECK(values && equals(values[0], "red fruit") && equals(values[1], "vegetable") && equals(values[2], "meat") && !values[3]);
    freeStrings(keys);
    freeStrings(values);

    DictItem *items = dict->items_dict(dict);
    CHECK(items && equals(items[1].key, "carrot") && equals(items[1].value, "vegetable"));
    CHECK(items && items[3].key == NULL && items[3].value == NULL);
    freeItems(items);

    Dict *empty = createDict();
    keys = empty->keys_dict(empty);
    items = empty->items_dict(empty);
    CHECK(keys && keys[0] == NULL && items && items[0].key == NULL);
    freeStrings(keys);
    freeItems(items);
    destroyDict(empty);
    destroyDict(dict);
}

static void testPop(void)
{
    Dict *dict = createDict();
    dict->insert_dict(dict, "Key1", "Value1");
    dict->insert_dict(dict, "Key2", "Value2");
    dict->insert_dict(dict, "Key3", "Value3");

    char *popped = dict->pop_dict(dict, "Key1", NULL);
    CHECK(equals(popped, "Value1") && dict->size_dict(dict) == 2 && !dict->exists_dict(dict, "Key1"));
    free(popped);

    popped = dict->pop_dict(dict, "Key1", NULL);
    CHECK(popped == NULL);
    popped = dict->pop_dict(dict, "Key1", "default");
    CHECK(equals(popped, "default") && dict->size_dict(dict) == 2);
    free(popped);

    DictItem *item = dict->popItem_dict(dict, "Key2");
    CHECK(item && equals(item->key, "Key2") && equals(item->value, "Value2") && dict->size_dict(dict) == 1);
    free(item->key);
    free(item->value);
    free(item);
    CHECK(dict->popItem_dict(dict, "Key2") == NULL);

    dict->insert_dict(dict, "Key4", "Value4");
    item = dict->popItem_dict(dict, NULL);
    CHECK(item && equals(item->key, "Key4") && dict->size_dict(dict) == 1);
    free(item->key);
    free(item->value);
    free(item);

    item = dict->popItem_dict(dict, NULL);
    CHECK(item && equals(item->key, "Key3") && dict->isEmpty_dict(dict));
    free(item->key);
    free(item->value);
    free(item);
    CHECK(dict->popItem_dict(dict, NULL) == NULL);
    destroyDict(dict);
}

static void testMergeCopyFromKeys(void)
{
    Dict *first = createDict();
    Dict *second = createDict();
    first->insert_dict(first, "apple", "fruit");
    first->insert_dict(first, "car", "mine");
    second->insert_dict(second, "car", "vehicle");
    second->insert_dict(second, "cat", "animal");

    first->merge_dict(first, second);
    CHECK(first->size_dict(first) == 3);
    CHECK(equals(first->get_dict(first, "car"), "mine") && equals(first->get_dict(first, "cat"), "animal"));
    CHECK(second->size_dict(second) == 2);
    first->merge_dict(first, first);
    CHECK(first->size_dict(first) == 3);

    Dict *copy = createDict();
    copy->insert_dict(copy, "stale", "value");
    copy->copy_dict(copy, first);
    CHECK(copy->size_dict(copy) == 3 && !copy->exists_dict(copy, "stale"));
    CHECK(equals(copy->get_dict(copy, "apple"), "fruit"));
    first->removeKey_dict(first, "apple");
    CHECK(equals(copy->get_dict(copy, "apple"), "fruit"));
    copy->copy_dict(copy, copy);
    CHECK(copy->size_dict(copy) == 3);

    Dict *fromKeys = createDict();
    const char *keys[] = {"One", "Two", "Three"};
    fromKeys->fromKeys_dict(fromKeys, keys, "Default Value", 3);
    CHECK(fromKeys->size_dict(fromKeys) == 3 && equals(fromKeys->get_dict(fromKeys, "Two"), "Default Value"));

    destroyDict(first);
    destroyDict(second);
    destroyDict(copy);
    destroyDict(fromKeys);
}

static void testGrowthAndLoadFactor(void)
{
    Dict *dict = createDict();
    CHECK(dict->loadFactor_dict(dict) == 0.0);
    char key[32];
    char value[32];
    for (int i = 0; i < 10000; i++)
    {
        snprintf(key, sizeof key, "key%d", i);
        snprintf(value, sizeof value, "value%d", i);
        dict->insert_dict(dict, key, value);
    }
    CHECK(dict->size_dict(dict) == 10000);
    CHECK(dict->loadFactor_dict(dict) > 0.0 && dict->loadFactor_dict(dict) <= 0.75);

    bool allFound = true;
    for (int i = 0; i < 10000; i++)
    {
        snprintf(key, sizeof key, "key%d", i);
        snprintf(value, sizeof value, "value%d", i);
        allFound = allFound && equals(dict->get_dict(dict, key), value);
    }
    CHECK(allFound);

    for (int i = 0; i < 10000; i += 2)
    {
        snprintf(key, sizeof key, "key%d", i);
        dict->removeKey_dict(dict, key);
    }
    CHECK(dict->size_dict(dict) == 5000 && !dict->exists_dict(dict, "key0") && dict->exists_dict(dict, "key1"));

    char **keys = dict->keys_dict(dict);
    CHECK(keys && equals(keys[0], "key1") && equals(keys[4999], "key9999") && keys[5000] == NULL);
    freeStrings(keys);
    destroyDict(dict);
}

static void testCollisions(void)
{
    Dict *dict = createDict();
    dict->hash_dict = constantHash;
    dict->insert_dict(dict, "a", "1");
    dict->insert_dict(dict, "b", "2");
    dict->insert_dict(dict, "c", "3");
    dict->removeKey_dict(dict, "b");
    CHECK(equals(dict->get_dict(dict, "a"), "1") && equals(dict->get_dict(dict, "c"), "3"));
    CHECK(dict->get_dict(dict, "b") == NULL && dict->size_dict(dict) == 2);
    for (int i = 0; i < 100; i++)
    {
        char key[16];
        snprintf(key, sizeof key, "k%d", i);
        dict->insert_dict(dict, key, key);
    }
    CHECK(dict->size_dict(dict) == 102 && equals(dict->get_dict(dict, "k99"), "k99"));
    destroyDict(dict);
}

int main(void)
{
    testInsertGetUpdate();
    testRemoveExistsClear();
    testOrderedViews();
    testPop();
    testMergeCopyFromKeys();
    testGrowthAndLoadFactor();
    testCollisions();
    destroyDict(NULL);
    printf("%d checks, %d failures\n", checks, failures);
    return failures == 0 ? 0 : 1;
}
