#ifndef GAME_SCRIPT_H
#define GAME_SCRIPT_H

#include <stdio.h>
#include "config.h"

struct Game_Script_Manager
{
    int current_script_id;
    bool script_read_flag;
};

struct Game_Script_Manager create_game_script_manager();
void advance_game_script(struct Game_Script_Manager *game_script_manager);
void run_game_script_manager(struct Game_Script_Manager *game_script_manager);
char* load_game_title();
char* load_game_script(const int id);
void free_script_content(char *script_content);

#endif