#include <stdio.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "game_map.h"

int main()
{
    cJSON *json = load_json_file(filename);
    if (!json)
    {
        printf("Failed to load JSON file!\n");
        return 1;
    }
    printf("JSON file loaded successfully.\n");

    cJSON_Delete(json);

    return 0;
}