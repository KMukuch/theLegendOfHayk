#ifndef GAME_QUEST
#define GAME_QUEST

#include <stdio.h>
#include <stdbool.h>
#include <cjson/cJSON.h>
#include "config.h"

struct Game_Quest_Manager
{
    struct Game_Quest *game_quest_array;
    int game_quest_array_size;
};

struct Game_Quest
{
    char game_quest_name[MAXNAME];
    char game_quest_description[MAXLINE];
    int current_quest_id;
    bool complete_flag;
    struct Game_Quest_Objective *game_quest_objective;
    Game_Quest_Type game_quest_type;
};

struct Game_Quest_Objective
{
    char objective_name[MAXNAME];
    char objective_description[MAXLINE];
    int game_quest_objective_id;
    bool complete_flag;
    struct Objective_Location objective_location;
};

struct Objective_Location
{
    struct Map *map;
    struct Location *location;
};

#endif