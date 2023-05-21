#include "map.h"

#include "limits.h"

void map_free(Map map) {
    int i;
    for (i = 0; i < MAP_SIZE; i++) {
        link_free(map->data[i]);
    }
    free(map);
}