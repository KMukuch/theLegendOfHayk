#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "game_map.h"
#include "json_utils.h"

#define FILENAME "../data/game_map.json"

struct Location create_location(const char  *location_name)
{
    struct Location location;

    strcpy(location.location_name, location_name);
    location.start_flag = false;
    location.connection_array = NULL;
    location.connection_array_size = 0;

    return location;
}

struct Location_Connection create_connection(const struct Location *location, int distance)
{
    struct Location_Connection connection;

    connection.location_array = location;
    connection.connection_distance = distance;

    return connection;
}

void set_connection(struct Location *location, struct Location_Connection *location_connection, int size)
{
    location->connection_array = location_connection;
    location->connection_array_size = size;
}

struct Map create_map(const char  *map_name, const char *map_ref)
{
    struct Map map;

    strcpy(map.map_name, map_name);
    strcpy(map.map_ref, map_ref);
    map.location_array = NULL;
    map.location_array_size = 0;

    return map;
}

struct Maps create_maps(const struct Map *map_array, int map_array_size)
{
    struct Maps maps;

    maps.map_array = map_array;
    maps.map_array_size = map_array_size;

    return maps;
}

struct Map* create_game_map(cJSON *json_file)
{
    int game_map_size = 0;
    
    struct Map *game_map;

    game_map_size = cJSON_GetArraySize(json_file);
    game_map = malloc(game_map_size * sizeof(struct Map));
    if (!game_map) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        cJSON_Delete(json_file);

        return NULL;
    }

    for (int i = 0; i < game_map_size; i++)
    {
        cJSON *json_item = cJSON_GetArrayItem(json_file, i);
        cJSON *json_node = cJSON_GetObjectItemCaseSensitive(json_item, "node");
        cJSON *json_map_ref = cJSON_GetObjectItemCaseSensitive(json_item, "map_ref");
        if (cJSON_IsString(json_node) && json_node->valuestring != NULL && cJSON_IsString(json_map_ref) && json_map_ref->valuestring != NULL) 
        {
            game_map[i] = create_map(json_node->valuestring, json_map_ref->valuestring);
        }
    }

    return game_map;
}

struct Location* create_location_array(cJSON *json_file)
{
    int location_array_size = 0;

    struct Location *location_array;

    location_array_size = cJSON_GetArraySize(json_file);
    location_array = malloc(location_array_size * sizeof(struct Location));
    if (!location_array) 
    {
        fprintf(stderr, "Memory allocation failed\n");

        return NULL;
    }

    for (int i = 0; i < location_array_size; i++)
    {
        cJSON *json_item = cJSON_GetArrayItem(json_file, i);
        cJSON *json_node = cJSON_GetObjectItemCaseSensitive(json_item, "node");
        cJSON *json_start_flag = cJSON_GetObjectItemCaseSensitive(json_item, "start");
        if (cJSON_IsString(json_node) && json_node->valuestring != NULL) 
        {
            location_array[i] = create_location(json_node->valuestring);
        }
        if (cJSON_IsBool(json_start_flag) && cJSON_IsTrue(json_start_flag)) 
        {
            location_array[i].start_flag = true;
        }
        
    }

    return location_array;
}

void set_connection_array(cJSON *json_file, int connection_array_size, struct Location *location_array)
{
    for (int i = 0; i < connection_array_size; i++)
    {
        int connection_size;
        struct Location_Connection *connection;

        cJSON *json_item = cJSON_GetArrayItem(json_file, i);
        cJSON *json_connection = cJSON_GetObjectItemCaseSensitive(json_item, "connection");

        connection_size = cJSON_GetArraySize(json_connection);
        if (connection_size > 0)
        {
            connection = malloc(connection_size * sizeof(struct Location_Connection));
            if (!connection)
            {
                fprintf(stderr, "Memory allocation failed\n");
                
                return;
            }
            
            for (int j = 0; j < connection_size; j++)
            {
                cJSON *json_connection_item = cJSON_GetArrayItem(json_connection, j);
                cJSON *json_node = cJSON_GetObjectItemCaseSensitive(json_connection_item, "node");
                cJSON *json_distance = cJSON_GetObjectItemCaseSensitive(json_connection_item, "distance");
                
                struct Location *target = find_game_location_by_name(json_node->valuestring, location_array, location_array_size);
                
                if (target && cJSON_IsNumber(json_distance)) 
                {
                    connection[j] = create_connection(target, json_distance->valueint);
                }
            }

            set_connection(&location_array[i], connection, connection_size);
        }
    }
}

struct Maps init_game_map()
{
    struct Maps game_maps;
    struct Map *game_map;

    cJSON *json_file = load_json_file(FILENAME);

    game_maps.map_array_size = cJSON_GetArraySize(json_file);
    game_map = create_game_map(json_file);
    for(int i = 0; i < game_maps.map_array_size; i++)
    {
        char map_ref_path[MAXLINE];
        snprintf(map_ref_path, sizeof(map_ref_path), "../data/%s", game_map[i].map_ref);

        cJSON *json_map_ref_file = load_json_file(map_ref_path);
        int location_array_size = cJSON_GetArraySize(json_map_ref_file);
        struct Location *location_array = create_location_array(json_map_ref_file);
        set_connection_array(json_map_ref_file, location_array_size, location_array);  
        
        game_map[i].location_array = location_array;
        game_map[i].location_array_size = location_array_size;

        cJSON_Delete(json_map_ref_file);
    }
    
    game_maps.map_array = game_map;
    cJSON_Delete(json_file);

    return game_maps;
}

struct Location* find_game_location_by_name(const char location_name[MAXNAME], struct Location *game_map, int game_map_size)
{
    bool location_flag = false;

    for(int i = 0; i < game_map_size; i++)
    {
        if(strcmp(location_name, game_map[i].location_name) == 0 && !location_flag)
        {
            location_flag = true;

            return &game_map[i];
        }
    }

    return NULL;
}

void free_game_map(struct Maps *maps)
{
    if (!maps || !maps->map_array)
        return;

    for (int i = 0; i < maps->map_array_size; i++) {
        struct Map *map = &maps->map_array[i];
        for (int j = 0; j < map->location_array_size; j++) {
            free(map->location_array[j].connection_array);
        }
        free(map->location_array);
    }

    free((void*)maps->map_array);
}