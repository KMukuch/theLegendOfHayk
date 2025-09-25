#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <cjson/cJSON.h>
#include "config.h"

struct Location {
    char location_name[MAXNAME];
    Location_Type location_type;
    struct Location *parent;
    struct Location **children;
    int children_count;
    struct Location **neighbours;
    int *distances;
    int neighbours_count;
};

struct Location create_location(const char *location_name, Location_Type location_type);
void set_children(struct Location *location, struct Location **children_array, int count);
void set_neighbours(struct Location *location, struct Location **neighbours, int *distances, int count);
cJSON* load_json_file(const char *filename);
cJSON* find_nodes(cJSON *json);
cJSON* find_connections(cJSON *json);

#endif