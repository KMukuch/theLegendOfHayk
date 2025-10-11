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
    struct Location_Connection *connection_array;
    int connection_array_size;
};

struct Location_Connection 
{
    const struct Location *location_array;
    int connection_distance;
};

struct Map
{
    char map_name[MAXNAME];
    char map_ref[MAXLINE];
    struct Location *location_array;
    int location_array_size;
};

struct Map_Connection 
{
    struct Map *map;
    int connection_distance;
};

struct Maps
{
    struct Map *map_array;
    int map_array_size;
};

struct Location create_location(const char *location_name);
struct Location_Connection create_connection(const struct Location *location, int distance);
void set_connection(struct Location *location, struct Location_Connection *location_connection, int size);

struct Map create_map(const char *map_name, const char *map_ref);
struct Maps create_maps(struct Map *map_array, int map_array_size);

struct Map* create_game_map(cJSON *json_file);
struct Maps init_game_map();

struct Location* find_game_location_by_name(const char location_name[MAXNAME], struct Location *location_array, int location_array_size);
const struct Location* find_location_in_maps_by_name(const char location_name[MAXNAME], const struct Maps *maps);

void free_game_map(struct Maps *maps);

#endif