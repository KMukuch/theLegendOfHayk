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
    loc.local_map_size = 0;
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

void init_locations_from_json(struct Location *map, cJSON *json_file, int map_size)
{
    for (int i = 0; i < map_size; i++)
    {
        cJSON *json_item = cJSON_GetArrayItem(json_file, i);
        cJSON *json_node = cJSON_GetObjectItemCaseSensitive(json_item, "node");
        cJSON *json_start_flag = cJSON_GetObjectItemCaseSensitive(json_item, "start");

        if (cJSON_IsString(json_node) && json_node->valuestring != NULL)
        {
            map[i] = create_location(json_node->valuestring, map_size);

            cJSON *json_local_map_file = find_local_map_by_ref(json_item);
            if (json_local_map_file != NULL)
            {
                map[i].local_map = init_local_map(json_local_map_file);
                map[i].local_map_size = map_size;
            }
        }

        if (cJSON_IsBool(json_start_flag) && cJSON_IsTrue(json_start_flag))
        {
            map[i].start_flag = true;
        }
    }
}

struct Location* init_local_map(cJSON *json_local_map_file)
{
    if (!json_local_map_file) return NULL;

    int local_map_size = cJSON_GetArraySize(json_local_map_file);
    struct Location *local_map = malloc(local_map_size * sizeof(struct Location));
    if (!local_map)
    {
        fprintf(stderr, "Memory allocation failed\n");
        cJSON_Delete(json_local_map_file);
        return NULL;
    }

    init_locations_from_json(local_map, json_local_map_file, local_map_size);

    if (!init_connections_from_json(local_map, json_local_map_file, local_map_size))
    {
        free_game_map(local_map);
        cJSON_Delete(json_local_map_file);
        return NULL;
    }

    cJSON_Delete(json_local_map_file);
    return local_map;
}

void set_connection(struct Location *location, struct Location_Connection *location_connection, int size)
{
    location->connections = location_connection;
    location->connections_count = size;
}

void set_connection_list(struct Location *game_map, cJSON *json_connection, struct Location_Connection *connection, int connection_size, int game_map_size)
{
    for (int j = 0; j < connection_size; j++)
    {
        cJSON *json_connection_item = cJSON_GetArrayItem(json_connection, j);
        cJSON *json_node = cJSON_GetObjectItemCaseSensitive(json_connection_item, "node");
        cJSON *json_distance = cJSON_GetObjectItemCaseSensitive(json_connection_item, "distance");

        struct Location *target = find_game_location_by_name(json_node->valuestring, game_map, game_map_size);

        if (target && cJSON_IsNumber(json_distance))
        {
            connection[j] = create_connection(target, json_distance->valueint);
        }
    }
}

bool init_connections_from_json(struct Location *game_map, cJSON *json_file, int game_map_size)
{
    int i = 0;
    bool success = true;

    while (i < game_map_size && success)
    {
        cJSON *json_item = cJSON_GetArrayItem(json_file, i);
        cJSON *json_connection = cJSON_GetObjectItemCaseSensitive(json_item, "connections");
        int connection_size = cJSON_GetArraySize(json_connection);

        if (connection_size > 0)
        {
            struct Location_Connection *connection;
            connection = malloc(connection_size * sizeof(struct Location_Connection));

            if (!connection)
            {
                fprintf(stderr, "Memory allocation failed\n");
                success = false;
            }
            else
            {
                set_connection_list(game_map, json_connection, connection, connection_size, game_map_size);
                set_connection(&game_map[i], connection, connection_size);
            }
        }
        i++;
    }

    return success;
}

struct Location* init_game_map()
{
    int game_map_size = 0;
    struct Location *game_map;
    cJSON *json_file;

    json_file = load_json_file(FILENAME);
    game_map_size = cJSON_GetArraySize(json_file);

    game_map = malloc(game_map_size * sizeof(struct Location));
    if (!game_map)
    {
        fprintf(stderr, "Memory allocation failed\n");
        cJSON_Delete(json_file);
        return NULL;
    }

    init_locations_from_json(game_map, json_file, game_map_size);

    if (!init_connections_from_json(game_map, json_file, game_map_size))
    {
        free_game_map(game_map);
        cJSON_Delete(json_file);
        return NULL;
    }

    cJSON_Delete(json_file);
    return game_map;
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

cJSON* find_local_map_by_ref(cJSON *json_item)
{
    cJSON *json_map_ref = cJSON_GetObjectItemCaseSensitive(json_item, "map_ref");
    if(cJSON_IsString(json_map_ref) && json_map_ref->valuestring != NULL)
    {
        char local_map_path[256];
        snprintf(local_map_path, sizeof(local_map_path), "../data/%s", json_map_ref->valuestring);
        json_map_ref = load_json_file(local_map_path);
    }

    return json_map_ref;
}

void free_game_map(struct Location *game_map)
{
    for (int i = 0; i < game_map[0].game_map_size; i++) 
    {
        free(game_map[i].connections);
    }
    free(game_map);
}