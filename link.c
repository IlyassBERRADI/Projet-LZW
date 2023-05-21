#include "link.h"

#include <string.h>

Link link_create(const char *str, uint32_t code, Link next) {
    Link new = malloc(sizeof(struct _link));
    new->str = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(new->str, str);
    new->code = code;
    new->next = next;
    return new;
}

void link_free(Link link) {
    if (link == NULL) return;
    link_free(link->next);
    free(link->str);
    free(link);
}
