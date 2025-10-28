#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "json_utils.h"
#include "game_map.h"
#include "game_npc.h"
#include "game_quest.h"

#define FILENAME "../data/game_quest.json"

struct Game_Quest_Manager create_game_quest_manager()
{
    struct Game_Quest_Manager game_quest_manager;

    game_quest_manager.game_quest_array = NULL;
    game_quest_manager.game_quest_array_size = 0;

    return game_quest_manager;
}

struct Game_Quest create_game_quest()
{
    struct Game_Quest game_quest;

    game_quest.game_quest_id = 0;
    game_quest.in_progress = false;
    game_quest.complete_flag = false;
    game_quest.game_quest_objective_array = NULL;
    game_quest.objective_array_size = 0;

    return game_quest;
}

struct Game_Quest_Objective create_game_quest_objective()
{
    struct Game_Quest_Objective game_quest_objective;

    game_quest_objective.game_quest_objective_id = 0;
    game_quest_objective.in_progress = false;
    game_quest_objective.complete_flag = false;
    game_quest_objective.objective_location = create_objective_location();

    return game_quest_objective;
}

struct Objective_Location create_objective_location()
{
    struct Objective_Location objective_location;

    objective_location.map = NULL;
    objective_location.location = NULL;

    return objective_location;
}

struct Game_Quest_Reference create_game_quest_reference()
{
    struct Game_Quest_Reference game_quest_reference;

    game_quest_reference.game_quest_id = 0;
    game_quest_reference.game_quest_objective_id = 0;

    return game_quest_reference;
}

void set_objective_location(cJSON *json_objective_location, struct Game_Quest_Objective *game_quest_objective, struct Maps *game_maps)
{
    cJSON *json_map = cJSON_GetObjectItemCaseSensitive(json_objective_location, "map");
    cJSON *json_location = cJSON_GetObjectItemCaseSensitive(json_objective_location, "location");
    if(cJSON_IsString(json_map) && json_map->valuestring != NULL)
    {
        game_quest_objective->objective_location.map = find_map_by_name(json_map->valuestring, game_maps->map_array, game_maps->map_array_size);
    }
    if(cJSON_IsString(json_location) && json_location->valuestring != NULL)
    {
        game_quest_objective->objective_location.location = find_location_in_maps_by_name(json_location->valuestring, game_maps);
    }
}

void set_quest_objective(cJSON *json_quest_objective, struct Game_Quest_Objective *game_quest_objective, struct Maps *game_maps)
{
    cJSON *json_objective_name = cJSON_GetObjectItemCaseSensitive(json_quest_objective, "name");
    cJSON *json_objective_description = cJSON_GetObjectItemCaseSensitive(json_quest_objective, "description");
    cJSON *json_objective_id = cJSON_GetObjectItemCaseSensitive(json_quest_objective, "id");
    cJSON *json_objective_location = cJSON_GetObjectItemCaseSensitive(json_quest_objective, "objective");

    if(cJSON_IsString(json_objective_name) && json_objective_name->valuestring != NULL)
    {
        strcpy(game_quest_objective->objective_name, json_objective_name->valuestring);
    }
    if(cJSON_IsString(json_objective_description) && json_objective_description->valuestring != NULL)
    {
        strcpy(game_quest_objective->objective_description, json_objective_description->valuestring);
    }
    if(cJSON_IsNumber(json_objective_id))
    {
        game_quest_objective->game_quest_objective_id = json_objective_id->valueint;
    }
    if(json_objective_location)
    {
        set_objective_location(json_objective_location, game_quest_objective, game_maps);
    }
}

void set_objective_array(cJSON *json_quest_objective, struct Game_Quest_Objective *objective_array, int objective_array_size, struct Maps *game_maps)
{
    for (int i = 0; i < objective_array_size; i++)
    {
        objective_array[i] = create_game_quest_objective();

        cJSON *json_objective_item = cJSON_GetArrayItem(json_quest_objective, i);
        set_quest_objective(json_objective_item, &objective_array[i], game_maps);
    }
}

void set_game_quest(cJSON *json_quest_item, struct Game_Quest *game_quest, struct Maps *game_maps)
{
    int objective_array_size = 0;

    struct Game_Quest_Objective *objective_array;

    cJSON *json_quest_name = cJSON_GetObjectItemCaseSensitive(json_quest_item, "name");
    cJSON *json_quest_description = cJSON_GetObjectItemCaseSensitive(json_quest_item, "description");
    cJSON *json_quest_id = cJSON_GetObjectItemCaseSensitive(json_quest_item, "id");
    cJSON *json_quest_objective = cJSON_GetObjectItemCaseSensitive(json_quest_item, "objective");

    objective_array_size = cJSON_GetArraySize(json_quest_objective);
    objective_array = malloc(objective_array_size * sizeof(struct Game_Quest_Objective));
    if (!objective_array) 
    {
        fprintf(stderr, "Memory allocation failed\n");

        return;
    }

    if(cJSON_IsString(json_quest_name) && json_quest_name->valuestring != NULL)
    {
        strcpy(game_quest->game_quest_name, json_quest_name->valuestring);
    }
    if(cJSON_IsString(json_quest_description) && json_quest_description->valuestring != NULL)
    {
        strcpy(game_quest->game_quest_description, json_quest_description->valuestring);
    }
    if(cJSON_IsNumber(json_quest_id))
    {
        game_quest->game_quest_id = json_quest_id->valueint;
    }
    if(json_quest_objective)
    {
        set_objective_array(json_quest_objective, objective_array, objective_array_size, game_maps);
        game_quest->game_quest_objective_array = objective_array;
        game_quest->objective_array_size = objective_array_size;
    }
}

void set_game_quest_reference_from_script(cJSON *json_file, const int game_script_id, struct Game_Quest_Reference *game_quest_reference)
{
    bool script_flag = false;
    
    cJSON *json_script = cJSON_GetObjectItemCaseSensitive(json_file, "script");
    cJSON *json_script_item = NULL;
    
    cJSON_ArrayForEach(json_script_item, json_script)
    {
        cJSON *json_script_item_id = cJSON_GetObjectItemCaseSensitive(json_script_item, "id");
        if(cJSON_IsNumber(json_script_item_id) && !script_flag)
        {
            if(json_script_item_id->valueint == game_script_id)
            {
                cJSON *json_script_item_quest_ref = cJSON_GetObjectItemCaseSensitive(json_script_item, "quest_ref");
                cJSON *json_quest_id = cJSON_GetObjectItemCaseSensitive(json_script_item_quest_ref, "quest_id");
                cJSON *json_objective_id = cJSON_GetObjectItemCaseSensitive(json_script_item_quest_ref, "objective_id");
                if(cJSON_IsNumber(json_quest_id) && cJSON_IsNumber(json_objective_id))
                {
                    game_quest_reference->game_quest_id = json_quest_id->valueint;
                    game_quest_reference->game_quest_objective_id = json_objective_id->valueint;
                    game_quest_reference->quest_handler = _in_progress;
                }
            }
        }
    }
}

void _in_progress(struct Game_Quest_Reference *game_quest_reference, struct Game_Quest_Manager *game_quest_manager)
{
    bool quest_flag = false;
    bool objective_flag = false;

    for(int i = 0; i < game_quest_manager->game_quest_array_size; i++)
    {
        struct Game_Quest *quest = &game_quest_manager->game_quest_array[i];
        if(quest->game_quest_id == game_quest_reference->game_quest_id && !quest_flag && !quest->in_progress)
        {
            quest_flag = true;
            for(int j = 0; j < quest->objective_array_size; j++)
            {
                struct Game_Quest_Objective *objective = &quest->game_quest_objective_array[j];
                if(objective->game_quest_objective_id == game_quest_reference->game_quest_objective_id && !objective_flag && !objective->in_progress)
                {
                    quest->in_progress = true;
                    objective->in_progress = true;
                }
            }
        }
    }
}

void _complete(struct Game_Quest_Reference *game_quest_reference, struct Game_Quest_Manager *game_quest_manager)
{

}

void init_game_quest_manager(struct Game_Quest_Manager *game_quest_manager, struct Maps *game_maps)
{
    int game_quest_array_size = 0;

    struct Game_Quest *game_quest_array;

    cJSON *json_file = load_json_file(FILENAME);

    game_quest_array_size = cJSON_GetArraySize(json_file);
    game_quest_array = malloc(game_quest_array_size * sizeof(struct Game_Quest));
    if (!game_quest_array) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        cJSON_Delete(json_file);

        return;
    }

    for (int i = 0; i < game_quest_array_size; i++)
    {
        game_quest_array[i] = create_game_quest();

        cJSON *json_quest_item = cJSON_GetArrayItem(json_file, i);
        set_game_quest(json_quest_item, &game_quest_array[i], game_maps);
    }
    
    game_quest_manager->game_quest_array = game_quest_array;
    game_quest_manager->game_quest_array_size = game_quest_array_size;

    cJSON_Delete(json_file);
}

void update_game_quest_manager(struct Game_Quest_Manager *game_quest_manager, struct Game_Quest_Reference *game_quest_reference)
{
    game_quest_reference->quest_handler(game_quest_reference, game_quest_manager);
}

void read_game_quests(struct Game_Quest_Manager *game_quest_manager)
{
    for(int i = 0; i < game_quest_manager->game_quest_array_size; i++)
    {
        struct Game_Quest *quest = &game_quest_manager->game_quest_array[i];
        printf("Quest #%d: %s\n", quest->game_quest_id, quest->game_quest_name);
        printf("Description: %s\n", quest->game_quest_description);
        printf("Completed: %s\n", quest->complete_flag ? "Yes" : "No");
        
        for(int j = 0; j < quest->objective_array_size; j++)
        {
            struct Game_Quest_Objective *objective = &quest->game_quest_objective_array[j];
            printf("Objective #%d: %s\n", objective->game_quest_objective_id, objective->objective_name);
            printf("Description: %s\n", objective->objective_description);
            printf("Completed: %s\n", objective->complete_flag ? "Yes" : "No");

            if (objective->objective_location.map)
                printf("Map: %s\n", objective->objective_location.map->map_name);
            if (objective->objective_location.location)
                printf("Location: %s\n", objective->objective_location.location->location_name);
        }
        printf("\n");
    }
}

void free_game_quest_manager(struct Game_Quest_Manager *quest_manager)
{
    if (!quest_manager || !quest_manager->game_quest_array)
        return;

    for (int i = 0; i < quest_manager->game_quest_array_size; i++)
    {
        struct Game_Quest *quest = &quest_manager->game_quest_array[i];
        free(quest->game_quest_objective_array);
    }

    free(quest_manager->game_quest_array);
}
