#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <stdio.h>
#include <cjson/cJSON.h>
#include "config.h"

struct Location 
{
    char location_name[MAXNAME];
    int game_map_size;
    Location_Type location_type;
    struct Location_Connection *connections;
    int connections_count;
};

struct Location_Connection 
{
    const struct Location *location;
    int connection_distance;
};

struct Location create_location(const char *location_name, int size, Location_Type location_type);
struct Location_Connection create_connection(const struct Location *location, int distance);
void set_connection(struct Location *location, struct Location_Connection *location_connection, int size);
Location_Type parse_location_type(const char *type_str);
struct Location* init_game_map();
void free_game_map(struct Location *game_map);

#endif