#ifndef GAME_QUEST_H
#define GAME_QUEST_H

#include <stdio.h>
#include <stdbool.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "game_map.h"

struct Objective_Location
{
    struct Map *map;
    struct Location *location;
};

struct Game_Quest_Objective
{
    char objective_name[MAXNAME];
    char objective_description[MAXDESCRIPTION];
    int game_quest_objective_id;
    bool in_progress;
    bool complete_flag;
    struct Objective_Location objective_location;
    Objective_Type objective_type;
};

struct Game_Quest
{
    char game_quest_name[MAXNAME];
    char game_quest_description[MAXDESCRIPTION];
    int game_quest_id;
    bool in_progress;
    bool complete_flag;
    struct Game_Quest_Objective *game_quest_objective_array;
    int objective_array_size;
    Game_Quest_Type game_quest_type;
};

struct Game_Quest_Manager
{
    struct Game_Quest *game_quest_array;
    int game_quest_array_size;
};

struct Game_Quest_Reference
{
    int game_quest_id;
    int game_quest_objective_id;
    void (*quest_handler)(struct Game_Quest_Reference*, struct Game_Quest_Manager*);
};

struct Game_Quest_Manager create_game_quest_manager();
struct Game_Quest create_game_quest();
struct Game_Quest_Objective create_game_quest_objective();
struct Objective_Location create_objective_location();
struct Game_Quest_Reference create_game_quest_reference();

void set_objective_location(cJSON *json_objective_location, struct Game_Quest_Objective *game_quest_objective, struct Maps *game_maps);
void set_quest_objective(cJSON *json_quest_objective, struct Game_Quest_Objective *game_quest_objective, struct Maps *game_maps);
void set_objective_array(cJSON *json_quest_objective_array, struct Game_Quest_Objective *objective_array, int objective_array_size, struct Maps *game_maps);
void set_game_quest(cJSON *json_quest_item, struct Game_Quest *game_quest, struct Maps *game_maps);

void set_game_quest_reference_from_script(cJSON *json_file, const int game_script_id, struct Game_Quest_Reference *game_quest_reference);

void _in_progress(struct Game_Quest_Reference *game_quest_reference, struct Game_Quest_Manager *game_quest_manager);
void _complete(struct Game_Quest_Reference *game_quest_reference, struct Game_Quest_Manager *game_quest_manager);

void init_game_quest_manager(struct Game_Quest_Manager *game_quest_manager, struct Maps *game_maps);

void update_game_quest_manager(struct Game_Quest_Manager *game_quest_manager, struct Game_Quest_Reference *game_quest_reference);

void read_game_quests(struct Game_Quest_Manager *game_quest_manager);

void free_game_quest_manager(struct Game_Quest_Manager *quest_manager);

#endif