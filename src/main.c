#include <stdio.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "game_map.h"

int main()
{
    cJSON *json = load_json_file("../data/game_map.json");
    if (!json)
    {
        printf("Failed to load JSON file!\n");
        return 1;
    }
    printf("JSON file loaded successfully.\n");

    return 0;
}