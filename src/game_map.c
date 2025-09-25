#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "game_map.h"

struct Location create_location(const char  *location_name, Location_Type location_type)
{
    struct Location loc;

    strcpy(loc.location_name, location_name);
    loc.location_type = location_type;
    loc.parent = NULL;
    loc.children = NULL;
    loc.children_count = 0;
    loc.neighbours = NULL;
    loc.distances = NULL;
    loc.neighbours_count = 0;

    return loc;
}

void set_children(struct Location *location, struct Location  **children_array, int count)
{
    location->children = children_array;
    location->children_count = count;

    for (int i = 0; i < count; i++) {
        children_array[i]->parent = location;
    }
}

void set_neighbours(struct Location *location, struct Location **neighbours, int *distances, int count)
{
    location->neighbours = neighbours;
    location->distances = distances;
    location->neighbours_count = count;
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

    struc Location *game_map;

    cJSON *json_file = load_json_file(FILENAME);
    cJSON *json_nodes = find_nodes(json_file);
    cJSON *json_connections = find_connections(json_nodes);

    game_map_size = cJSON_GetArraySize(json_nodes);
    game_map = malloc(game_map_size * sizeof(struct Location));

    

    cJSON_Delete(json_file);

    return game_map;
}

cJSON* find_nodes(cJSON *json)
{
    cJSON *json_nodes = NULL;
    cJSON *json_container = json;
    if (!json)
    {
        printf("Failed to load JSON file!\n");
        return 1;
    }
    
    json_regions = cJSON_GetObjectItemCaseSensitive(json_container, "name");

    return json_regions;
}

cJSON* find_connections(cJSON *json)
{
    cJSON *json_cities = NULL;
    cJSON *json_container = json;
    if (!json)
    {
        printf("Failed to load JSON file!\n");
        return 1;
    }
    
    json_cities = cJSON_GetObjectItemCaseSensitive(json_container, "city");

    return json_cities;
}