#include "mapen.h"

#include <string.h>
#include <limits.h>

#define SIZE 256
#define CLEAR_CODE 256
#define END_CODE 257

struct _mapen {
    Link data[SIZE];
    uint32_t next_code;
};

/**
 * @brief Get the hash value of the given str.
 */
uint32_t mapen_hash(const char* str) {
    uint32_t hash = 0;
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        hash = hash * hash + str[i];
    }
    return hash % SIZE;
}

/**
 * @brief Create a new map for encoding.
 */
Mapen mapen_create() {
    Mapen map = calloc(1, sizeof(struct _mapen));
    short i;
    char str[2] = " ";
    for (i = 0; i < UCHAR_MAX; i++) {
        str[0] = i;
        mapen_add_str(map, str);
    }
    /* Skip 2 values corresponding to CLEAR_CODE and END_CODE */
    map->next_code += 2;
    return map;
}

/**
 * @brief Free the map.
 */
void mapen_free(Mapen map) {
    int i;
    for (i = 0; i < SIZE; i++) {
        link_free(map->data[i]);
    }
    free(map);
}

/**
 * @brief Get the code for given str.
 * @param code The code corresponding to the str parameter if it exist in the map.
 * @return int Return 1 if str is in the map, 0 if not.
 */
int mapen_get_code(Mapen map, const char* str, uint32_t* code) {
    uint32_t hash = mapen_hash(str);
    Link link = map->data[hash];
    for (link = map->data[hash]; link != NULL; link = link->next) {
        if (strcmp(str, link->str) == 0) {
            /* Code found */
            *code = link->code;
            return 1;
        }
    }
    /* Code not found */
    return 0;
}

/**
 * @brief Add the str to the map and create a new code for it.
 * @param str 
 */
void mapen_add_str(Mapen map, const char* str) {
    uint32_t hash = mapen_hash(str);
    Link link = link_create(str, map->next_code++, map->data[hash]);
    map->data[hash] = link;
}
