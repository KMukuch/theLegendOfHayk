#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <cjson/cJSON.h>
#include "config.h"

struct Location {
    char location_name[MAXNAME];
    int game_map_size;
    Location_Type location_type;
    struct Location **connections;
    int connections_count;
};

struct Location create_location(const char *location_name, int size, Location_Type location_type);
cJSON* load_json_file(const char *filename);
struct Location* init_game_map();
// cJSON* find_nodes(cJSON *json);
cJSON* find_connections(cJSON *json);

#endif