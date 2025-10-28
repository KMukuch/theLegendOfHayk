#ifndef GAME_SCRIPT_H
#define GAME_SCRIPT_H

#include <stdio.h>
#include "config.h"
#include "game_quest.h"

struct Game_Script_Manager
{
    int current_script_id;
    Script_Command_Type script_command_type;
};

struct Game_Script_Manager create_game_script_manager();

void advance_game_script(struct Game_Script_Manager *game_script_manager);
void run_game_script_manager(struct Game_Script_Manager *game_script_manager, struct Game_Quest_Reference *game_quest_reference);

char* load_game_title();
char* load_game_script(cJSON *json_file, const int id, bool *pause_flag);

void free_script_content(char *script_content);

#endif