#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "game_map.h"
#include "json_utils.h"

#define FILENAME "../data/game_map.json"

struct Location create_location(const char  *location_name, int size, Location_Type location_type)
{
    struct Location loc;

    strcpy(loc.location_name, location_name);
    loc.game_map_size = size;
    loc.location_type = location_type;
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

Location_Type parse_location_type(const char *type_str)
{
    if (strcmp(type_str, "REGION") == 0) return REGION;
    if (strcmp(type_str, "CITY") == 0) return CITY;
    if (strcmp(type_str, "VILLAGE") == 0) return VILLAGE;
    return DEFAULT;
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
    if (!game_map) {
        fprintf(stderr, "Memory allocation failed\n");
        cJSON_Delete(json_file);
        return NULL;
    }

    for (int i = 0; i < game_map_size; i++)
    {
        cJSON *json_item = cJSON_GetArrayItem(json_file, i);
        cJSON *json_node = cJSON_GetObjectItemCaseSensitive(json_item, "node");
        cJSON *json_type = cJSON_GetObjectItemCaseSensitive(json_item, "type");
        if (cJSON_IsString(json_node) && json_node->valuestring != NULL && cJSON_IsString(json_type) && json_type->valuestring != NULL) 
        {
            game_map[i] = create_location(json_node->valuestring, game_map_size, parse_location_type(json_type->valuestring));
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

// cJSON* find_nodes(cJSON *json)
// {
//     cJSON *json_nodes = NULL;
//     if (!json)
//     {
//         printf("Failed to load JSON file!\n");
//         return NULL;
//     }
    
//     json_nodes = cJSON_GetObjectItemCaseSensitive(json, "name");

//     return json_nodes;
// }

// cJSON* find_connections(cJSON *json)
// {
//     cJSON *json_connection = NULL;
//     if (!json)
//     {
//         printf("Failed to load JSON file!\n");
//         return NULL;
//     }
    
//     json_connection = cJSON_GetObjectItemCaseSensitive(json, "connection");

//     return json_connection;
// }