/**
 * @file link.h
 * @brief A link inside a map.
 */
#ifndef __LINK_H__
#define __LINK_H__

#include <stdlib.h>
#include <stdint.h>
#include "str.h"

/**
 * @brief A link of a dictionary.
 */
typedef struct _link {
    Str str;
    uint32_t code;
    struct _link* next;
} *Link;

/**
 * @brief Create a new link.
 * @param str A copy will be created in the new link.
 * @return Link 
 */
Link link_create(const Str str, uint32_t code, Link next);

/**
 * @brief Free a link and all childs in link->next.
 */
void link_free(Link link);

#endif