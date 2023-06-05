/**
 * @file mapen.h
 * @brief Dictionary used for encoding with LZW algorithm
 */
#ifndef __MAPEN_H__
#define __MAPEN_H__

#include <stdlib.h>
#include "link.h"
#include "map.h"

/**
 * @brief Create a new map for encoding.
 */
Map mapen_create();

/**
 * @brief Get the code for given str.
 * @param code The code corresponding to the str parameter,
 * and don't modify it if str does not exist.
 * @return int Return 1 if str is in the map, 0 if not.
 */
int mapen_get_code(Map map, const Str str, uint32_t* code);

/**
 * @brief Add the str to the map and create a new code for it.
 * @param str A copy of this value will be added to the map.
 */
void mapen_add_str(Map map, const Str str);

#endif