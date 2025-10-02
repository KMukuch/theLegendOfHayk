#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "json_utils.h"
#include "npc.h"

#define FILENAME "../data/npc.json"

struct NPC create_npc()
{
    struct NPC npc;

    npc.current_location = NULL;
    npc.flag = false;
}

char* json_get_dialogue(char *npc_name, const int id);
{
    cJSON *json_file = load_json_file(FILENAME);
    cJSON *json_item = NULL;

    cJSON_ArrayForEach(json_item, json_file)
    {
        cJSON *json_name = cJSON_GetObjectItemCaseSensitive(json_item, "name");
        bool found = false;
        if(cJSON_IsString(json_name) && json_name->valuestring != NULL && !found)
        {
            if(strcmp(npc_name, json_name->valuestring) == 0)
            {
                
            }
        }
    }

    cJSON_Delete(json_file);
}