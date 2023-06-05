#include "map.h"

#include "limits.h"

void map_free(Map map) {
    int i;
    for (i = 0; i < MAP_SIZE; i++) {
        link_free(map->data[i]);
    }
    free(map);
}

int map_count(Map map) {
    int count = 0;
    int i;
    Link l;
    for (i = 0; i < MAP_SIZE; i++) {
        l = map->data[i];
        while (l != NULL) {
            count++;
            l = l->next;
        }
    }
    return count;
}

int map_next_code(Map map) { return map->next_code; }
