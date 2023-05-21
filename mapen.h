/**
 * @file mapen.h
 * @brief Dictionary used for encoding with LZW algorithm
 */
#ifndef __MAPEN_H__
#define __MAPEN_H__

#include <stdlib.h>
#include "link.h"

#define CLEAR_CODE 256
#define END_CODE 257

typedef struct _mapen *Mapen;

/**
 * @brief Create a new map for encoding.
 */
Mapen mapen_create();

/**
 * @brief Free the map.
 */
void mapen_free(Mapen map);

/**
 * @brief Get the code for given str.
 * @param code The code corresponding to the str parameter,
 * and don't modify it if str does note exist.
 * @return int Return 1 if str is in the map, 0 if not.
 */
int mapen_get_code(Mapen map, const char* str, uint32_t* code);

/**
 * @brief Add the str to the map and create a new code for it.
 * @param str 
 */
void mapen_add_str(Mapen map, const char* str);

#endif