#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "config.h"

struct Location create_location(char  *location_name, Location_Type location_type)
{
    struct Location loc;

    strcpy(loc.location_name, location_name);
    loc.location_type = location_type;
    loc.parent = NULL;
    loc.children = NULL;
    loc.children_count = 0;
    loc.neighbours = NULL;
    loc.neighbours_count = 0;

    return loc;
}

void set_children(struct Location *location, struct Location  **children_array, int count)
{
    location->children = children_array;
    location->children_count = count;

    for (int i = 0; i < count; i++) {
        children_array[i]->parent = location;
    }
}

void set_neighbors(struct Location *location, struct Location **neighbours_array, int count)
{
    location->neighbours_array = neighbours_array;
    location->neighbours_count = count;
}