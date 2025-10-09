#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <stdio.h>
#include <stdbool.h>
#include <cjson/cJSON.h>
#include "config.h"

struct Location 
{
    char location_name[MAXNAME];
    bool start_flag;
    int game_map_size;
    struct Location *local_map;
    int local_map_size;
    struct Location_Connection *connections;
    int connections_count;
};

struct Location_Connection 
{
    const struct Location *location;
    int connection_distance;
};

struct Location create_location(const char *location_name, int size);
struct Location_Connection create_connection(const struct Location *location, int distance);
void set_connection(struct Location *location, struct Location_Connection *location_connection, int size);
void set_connection_list(struct Location *game_map, cJSON *json_connection, struct Location_Connection *connection, int connection_size, int game_map_size);
void init_locations_from_json(struct Location *game_map, cJSON *json_file, int game_map_size);
bool init_connections_from_json(struct Location *game_map, cJSON *json_file, int game_map_size);
struct Location* init_local_map(cJSON *json_local_map_file);
struct Location* init_game_map();
struct Location* find_game_location_by_name(const char location_name[MAXNAME], struct Location *game_map, int game_map_size);
cJSON* find_local_map_by_ref(cJSON *json_item);
void free_game_map(struct Location *game_map);

#endif