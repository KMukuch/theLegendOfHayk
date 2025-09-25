#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "game_map.h"

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

cJSON* load_json_file(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        perror("Error opening file");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    rewind(fp);

    char *buffer = malloc(len + 1);
    if (!buffer)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        return NULL;
    }

    if (fread(buffer, 1, len, fp) != len)
    {
        fprintf(stderr, "Error reading file\n");
        free(buffer);
        fclose(fp);
        return NULL;
    }
    buffer[len] = '\0';
    fclose(fp);

    cJSON *json = cJSON_Parse(buffer);
    free(buffer);

    if (!json)
    {
        fprintf(stderr, "JSON parse error: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }

    return json;
}

struct Location* init_game_map()
{
    int game_map_size = 0;

    struct Location *game_map;

    cJSON *json_file = load_json_file(FILENAME);
    // cJSON *json_nodes = find_nodes(json_file);
    cJSON *json_connection = find_connections(json_file);

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
        cJSON *item = cJSON_GetArrayItem(json_file, i);
        cJSON *name = cJSON_GetObjectItemCaseSensitive(item, "name");
        if (cJSON_IsString(name) && name->valuestring != NULL) {
            game_map[i] = create_location(name->valuestring, game_map_size, DEFAULT);

            cJSON *connection = find_connections(item);
            cJSON *connection_item = NULL;
            cJSON_ArrayForEach(connection_item, connection)
            {
                
            }
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

cJSON* find_connections(cJSON *json)
{
    cJSON *json_connection = NULL;
    if (!json)
    {
        printf("Failed to load JSON file!\n");
        return NULL;
    }
    
    json_connection = cJSON_GetObjectItemCaseSensitive(json, "connection");

    return json_connection;
}