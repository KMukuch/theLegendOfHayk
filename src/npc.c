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

    return npc;
}

void set_npc_location(struct NPC *npc)
{

}

int get_npc_location(const struct NPC *npc)
{


    return 0;
}

void init_game_npc()
{
    
}

char* json_get_dialogue(char *npc_name, const int id)
{
    bool npc_flag = false;
    bool npc_dialogue_flag = false;

    char *content = NULL;

    cJSON *json_file = load_json_file(FILENAME);
    cJSON *json_item = NULL;

    cJSON_ArrayForEach(json_item, json_file)
    {
        cJSON *json_name = cJSON_GetObjectItemCaseSensitive(json_item, "name");
        if(cJSON_IsString(json_name) && json_name->valuestring != NULL && !npc_flag)
        {
            if(strcmp(npc_name, json_name->valuestring) == 0)
            {
                npc_flag = true;
                cJSON *json_dialogue = cJSON_GetObjectItemCaseSensitive(json_item, "dialogue");
                cJSON *json_dialogue_item = NULL;
                cJSON_ArrayForEach(json_dialogue_item, json_dialogue)
                {
                    cJSON *json_dialogue_item_id = cJSON_GetObjectItemCaseSensitive(json_dialogue_item, "id");
                    if(cJSON_IsNumber(json_dialogue_item_id) && !npc_dialogue_flag)
                    {
                        if(json_dialogue_item_id->valueint == id)
                        {
                            npc_dialogue_flag = true;
                            cJSON *json_dialogue_item_content = cJSON_GetObjectItemCaseSensitive(json_dialogue_item, "content");
                            if(cJSON_IsString(json_dialogue_item_content) && json_dialogue_item_content->valuestring != NULL)
                            {
                                int dialogue_content_size = strlen(json_dialogue_item_content->valuestring);
                                content = malloc(dialogue_content_size + 1);
                                if (!content)
                                {
                                    fprintf(stderr, "Memory allocation failed\n");
                                    cJSON_Delete(json_file);
                                    return NULL;
                                }
                                strcpy(content, json_dialogue_item_content->valuestring);
                            }
                        }
                    }
                }
            }
        }
    }

    cJSON_Delete(json_file);

    return content;
}

void free_dialogue_content(char *dialogue_content)
{
    free(dialogue_content);
}