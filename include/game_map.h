#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <cjson/cJSON.h>
#include "config.h"

struct Location {
    char location_name[MAXNAME];
    enum Location_Type location_type;
    struct Location *parent;
    struct Location **children;
    int children_count;
    struct Location **neighbours;
    int neighbours_count;
};

struct Location create_location(const char *location_name, Location_Type location_type);
void set_children(struct Location *location, struct Location **children_array, int count);
void set_neighbors(struct Location *location, struct Location **neighbours_array, int count);
cJSON* load_json_file(const char *filename);
cJSON* find_regions(cJSON *json);
cJSON* find_cities(cJSON *json);

#endif