/**
 * @file mapde.h
 * @brief Dictionary used for decoding with LZW algorithm
 */
#ifndef __MAPDE_H__
#define __MAPDE_H__

#include <stdlib.h>
#include "link.h"
#include "map.h"

/**
 * @brief Create a new map for encoding.
 */
Map mapde_create();

/**
 * @brief Get the str for given code.
 * @return Return the string attached to the code,
 * or NULL if the code does not exist.
 */
char* mapde_get_str(Map map, uint32_t code);

/**
 * @brief Add the str to the map and create a new code for it.
 * @param str 
 */
void mapde_add_str(Map map, const char* str);

#endif