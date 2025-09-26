#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <stdio.h>
#include <cjson/cJSON.h>
#include "config.h"

struct Location {
    char location_name[MAXNAME];
    int game_map_size;
    Location_Type location_type;
    struct Location_Connection *connections;
    int connections_count;
};

struct Location_Connection {
    const struct Location *location;
    int connection_distance;
    int connection_size;
};

struct Location create_location(const char *location_name, int size, Location_Type location_type);
struct Location_Connection create_connection(const struct Location *location, int distance, int size);
Location_Type parse_location_type(const char *type_str);
cJSON* load_json_file(const char *filename);
struct Location* init_game_map();
// cJSON* find_nodes(cJSON *json);
// cJSON* find_connections(cJSON *json);

#endif