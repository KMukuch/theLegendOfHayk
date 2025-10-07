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
struct Location* init_game_map();
void free_game_map(struct Location *game_map);

#endif