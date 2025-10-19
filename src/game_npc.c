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
    npc.flag = false;
    npc.dialogue_id = 0;

    return npc;
}

struct NPCs create_npcs()
{
    struct NPCs npcs;

    npcs.npc_array = NULL;
    npcs.npc_array_size = 0;

    return npcs;
}

struct NPCs init_game_npcs(const struct Maps *game_maps)
{
    int i, game_npc_size;
    struct NPCs game_npcs;
    struct NPC *game_npc;
    
    cJSON *json_file = load_json_file(FILENAME);
    cJSON *json_item = NULL;

    game_npcs = create_npcs();
    game_npc_size = cJSON_GetArraySize(json_file);
    game_npc = malloc(game_npc_size * sizeof(struct NPC));
    i = 0;
    cJSON_ArrayForEach(json_item, json_file)
    {
        cJSON *json_name = cJSON_GetObjectItemCaseSensitive(json_item, "name");
        if(cJSON_IsString(json_name) && json_name->valuestring != NULL)
        {
            game_npc[i] = create_npc(json_name->valuestring);

            cJSON *json_npc_location = cJSON_GetObjectItemCaseSensitive(json_item, "npc_location");
            cJSON *json_map = cJSON_GetObjectItemCaseSensitive(json_npc_location, "map");
            cJSON *json_location = cJSON_GetObjectItemCaseSensitive(json_npc_location, "location");
            if(cJSON_IsString(json_map) && json_map->valuestring != NULL)
            {
                game_npc[i].npc_location.map = find_map_by_name(json_map->valuestring, game_maps->map_array, game_maps->map_array_size);
            }
            if(cJSON_IsString(json_location) && json_location->valuestring != NULL)
            {
                game_npc[i].npc_location.location = find_location_in_maps_by_name(json_location->valuestring, game_maps);
            }
        }
        i++;
    }

    game_npcs.npc_array = game_npc;
    game_npcs.npc_array_size = game_npc_size;

    cJSON_Delete(json_file);

    return game_npcs;
}

void free_game_npcs(struct NPCs *npcs)
{
    free(npcs->npc_array);
    npcs->npc_array = NULL;
    npcs->npc_array_size = 0;
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