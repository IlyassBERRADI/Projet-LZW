#include "mapen.h"

#include <string.h>
#include <limits.h>

/**
 * @brief Get the hash value of the given str.
 */
uint32_t mapen_hash(const Str str) {
    uint32_t hash = 0;
    int i;
    for (i = 0; i < str->size; i++) {
        hash = hash * hash + str->data[i];
    }
    return hash % MAP_SIZE;
}

Map mapen_create() {
    Map map = calloc(1, sizeof(struct _map));
    short i;
    Str str = str_create(1);
    for (i = 0; i <= UCHAR_MAX; i++) {
        str_empty(str);
        str_append(str, (char)i);
        mapen_add_str(map, str);
    }
    /* Skip 2 values corresponding to CLEAR_CODE and END_CODE */
    map->next_code += 2;
    return map;
}

int mapen_get_code(Map map, const Str str, uint32_t* code) {
    uint32_t hash = mapen_hash(str);
    Link link = map->data[hash];
    for (link = map->data[hash]; link != NULL; link = link->next) {
        if (str_equals(str, link->str)) {
            /* Code found */
            *code = link->code;
            return 1;
        }
    }
    /* Code not found */
    return 0;
}

void mapen_add_str(Map map, const Str str) {
    uint32_t hash = mapen_hash(str);
    Link link = link_create(str, map->next_code++, map->data[hash]);
    map->data[hash] = link;
}