#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "game_map.h"
#include "json_utils.h"

#define FILENAME "../data/game_map.json"

struct Location create_location(const char  *location_name, int size)
{
    struct Location loc;

    strcpy(loc.location_name, location_name);
    loc.start_flag = false;
    loc.game_map_size = size;
    loc.local_map = NULL;
    loc.connections = NULL;
    loc.connections_count = 0;

    return loc;
}

struct Location_Connection create_connection(const struct Location *location, int distance)
{
    struct Location_Connection con;

    con.location = location;
    con.connection_distance = distance;

    return con;
}

void set_connection(struct Location *location, struct Location_Connection *location_connection, int size)
{
    location->connections = location_connection;
    location->connections_count = size;
}

struct Location* init_game_map()
{
    int game_map_size = 0;

    struct Location *game_map;

    cJSON *json_file = load_json_file(FILENAME);
    // cJSON *json_nodes = find_nodes(json_file);

    game_map_size = cJSON_GetArraySize(json_file);
    // printf("%i\n", game_map_size);
    game_map = malloc(game_map_size * sizeof(struct Location));
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
        cJSON *json_start_flag = cJSON_GetObjectItemCaseSensitive(json_item, "start");
        if (cJSON_IsString(json_node) && json_node->valuestring != NULL) 
        {
            game_map[i] = create_location(json_node->valuestring, game_map_size);
        }
        if (cJSON_IsBool(json_start_flag) && cJSON_IsTrue(json_start_flag)) 
        {
            game_map[i].start_flag = true;
        }
        
    }

    for (int i = 0; i < game_map_size; i++)
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
                cJSON_Delete(json_file);
                return NULL;
            }
            
            for (int j = 0; j < connection_size; j++)
            {
                cJSON *json_connection_item = cJSON_GetArrayItem(json_connection, j);
                cJSON *json_node = cJSON_GetObjectItemCaseSensitive(json_connection_item, "node");
                cJSON *json_distance = cJSON_GetObjectItemCaseSensitive(json_connection_item, "distance");
                
                struct Location *target = NULL;
                bool found = false;

                for (int k = 0; k < game_map_size && !found; k++) 
                {
                    if (strcmp(game_map[k].location_name, json_node->valuestring) == 0) 
                    {
                        target = &game_map[k];
                        found = true;
                    }
                }
                
                if (target && cJSON_IsNumber(json_distance)) 
                {
                    connection[j] = create_connection(target, json_distance->valueint);
                }
            }
            set_connection(&game_map[i], connection, connection_size);
        }
    }

    cJSON_Delete(json_file);

    return game_map;
}

void free_game_map(struct Location *game_map)
{
    for (int i = 0; i < game_map[0].game_map_size; i++) 
    {
        free(game_map[i].connections);
    }
    free(game_map);
}