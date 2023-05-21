#ifndef __LINK_H__
#define __LINK_H__

#include <stdlib.h>
#include <stdint.h>

/**
 * @brief A link of a dictionary.
 */
typedef struct _link {
    char* str;
    uint32_t code;
    struct _link* next;
} *Link;

/**
 * @brief Create a new link.
 * @param str A copy will be created in the new link.
 * @return Link 
 */
Link link_create(const char* str, uint32_t code, Link link);

/**
 * @brief Free a link and all childs in link->next.
 */
void link_free(Link link);

#endif