#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "config.h"

struct Location create_location(const char  *location_name, Location_Type location_type)
{
    struct Location loc;

    strcpy(loc.location_name, location_name);
    loc.location_type = location_type;
    loc.parent = NULL;
    loc.children = NULL;
    loc.children_count = 0;
    loc.neighbours = NULL;
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

void set_neighbors(struct Location *location, struct Location **neighbours_array, int count)
{
    location->neighbours_array = neighbours_array;
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

cJSON* find_regions(cJSON *json)
{

}

cJSON* find_cities(cJSON *json)
{
    
}