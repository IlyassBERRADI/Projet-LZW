/**
 * @file map.h
 * @brief Dictionary common to encoding and decoding.
 */
#ifndef __MAP_H__
#define __MAP_H__

#include "link.h"

#define MAP_SIZE 256
#define CLEAR_CODE 256
#define END_CODE 257

typedef struct _map {
    Link data[MAP_SIZE];
    uint32_t next_code;
} *Map;

/**
 * @brief Free the map.
 */
void map_free(Map map);

/**
 * @brief Count all elements from the map.
 * @note Using map_next_code is faster for almost the same result,
 * but this function also check that the map is well formed.
 */
int map_count(Map map);

/**
 * @brief Get the next code to add to the map.
 */
int map_next_code(Map map);

#endif