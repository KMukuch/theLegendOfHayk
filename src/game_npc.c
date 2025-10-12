#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "json_utils.h"
#include "game_map.h"
#include "game_npc.h"

#define FILENAME "../data/game_npc.json"

struct NPC create_npc(const char *npc_name)
{
    struct NPC npc;

    strcpy(npc.npc_name, npc_name);
    npc.current_location = NULL;
    npc.flag = false;
    npc.dialogue_id = 0;

    return npc;
}

void set_npc_location_by_name(cJSON *json_item, struct NPC *npc, const struct Location *game_map, int game_map_size)
{
    bool location_flag = false;

    char location_name[MAXNAME];

    cJSON *json_location_name = cJSON_GetObjectItemCaseSensitive(json_item, "location");
    if(cJSON_IsString(json_location_name) && json_location_name->valuestring != NULL)
    {
        strcpy(location_name, json_location_name->valuestring);
    }

    for(int i = 0; i < game_map_size; i++)
    {
        if(strcmp(location_name, game_map[i].location_name) == 0 && !location_flag)
        {
            location_flag = true;
            npc->current_location = &game_map[i];
        }
    }
}

int get_game_npc_size()
{
    int game_npc_size = 0;
    
    cJSON *json_file = load_json_file(FILENAME);
    game_npc_size = cJSON_GetArraySize(json_file);

    return game_npc_size;
}

struct NPC* init_game_npc(const struct Maps *game_maps)
{
    int i, game_npc_size;
    struct NPC *game_npc;
    
    cJSON *json_file = load_json_file(FILENAME);
    cJSON *json_item = NULL;

    game_npc_size = cJSON_GetArraySize(json_file);
    game_npc = malloc(game_npc_size * sizeof(struct NPC));
    i = 0;
    cJSON_ArrayForEach(json_item, json_file)
    {
        cJSON *json_name = cJSON_GetObjectItemCaseSensitive(json_item, "name");
        if(cJSON_IsString(json_name) && json_name->valuestring != NULL)
        {
            game_npc[i] = create_npc(json_name->valuestring);

            cJSON *json_location_name = cJSON_GetObjectItemCaseSensitive(json_item, "location");
            if(cJSON_IsString(json_location_name) && json_location_name->valuestring != NULL)
            {
                game_npc[i].current_location = find_location_in_maps_by_name(json_location_name->valuestring, game_maps);
            }
        }
        i++;
    }
    cJSON_Delete(json_file);

    return game_npc;
}

void free_game_npc(struct NPC *game_npc)
{
    free(game_npc);
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