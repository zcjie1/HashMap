#include "./include/HashMap.h"
#include "./include/HashMapIterator.h"

#define Put(map, key, value) map->put(map, (void *)key, (void *)value);
#define Get(map, key) (char *)map->get(map, (void *)key)
#define Remove(map, key) map->remove(map, (void *)key)
#define Existe(map, key) map->exists(map, (void *)key)

int main() {

    HashMap map = createHashMap(NULL, NULL);
    Put(map, "asdfasdf", "asdfasdfds");
    Put(map, "sasdasd", "asdfasdfds");
    Put(map, "asdhfgh", "asdfasdfds");
    Put(map, "4545", "asdfasdfds");
    Put(map, "asdfaasdasdsdf", "asdfasdfds");
    Put(map, "asdasg", "asdfasdfds");
    Put(map, "qweqeqwe", "asdfasdfds");

    printf("key: 4545, exists: %s\n", Existe(map, "4545") ? "true" : "false");
    printf("4545: %s\n", (char*)Get(map, "4545"));
    printf("remove 4545 %s\n", Remove(map, "4545") ? "true" : "false");
    printf("remove 4545 %s\n", Remove(map, "4545") ? "true" : "false");
    printf("key: 4545, exists: %s\n", Existe(map, "4545") ? "true" : "false");

    HashMapIterator iterator = createHashMapIterator(map);
    while (hasNextHashMapIterator(iterator)) {
        iterator = nextHashMapIterator(iterator);
        printf("{ key: %s, value: %s, list_index: %d }\n",
            (char *)iterator->entry->key, (char *)iterator->entry->value, iterator->list_index);
    }

    map->clear(map);
    freeHashMapIterator(&iterator);
    free(map);

    return 0;
}