#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include "config.h"

struct Location {
    char location_name[MAXNAME];
    enum Location_Type location_type;
    struct Location *parent;
    struct Location **children;
    int children_count;
    struct Location **neighbors;
    int neighbors_count;
};

Location create_location(char* location_name, Location_Type location_type);
void init_world(Location world[], int* world_size);

#endif