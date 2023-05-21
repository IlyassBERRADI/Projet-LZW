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

#endif