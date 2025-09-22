#include <stdio.h>
#include "config.h"
#include "game_map.h"

int main()
{
    cJSON *json = load_json_file("data.json");
    process_regions(json);
    cJSON_Delete(json);

    return 0;
}