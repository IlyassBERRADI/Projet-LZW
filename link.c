#include "link.h"

#include <string.h>

Link link_create(const Str str, uint32_t code, Link next) {
    Link new = malloc(sizeof(struct _link));
    new->str = str_copy(str, str->size);
    new->code = code;
    new->next = next;
    return new;
}

void link_free(Link link) {
    if (link == NULL) return;
    link_free(link->next);
    str_free(link->str);
    free(link);
}
