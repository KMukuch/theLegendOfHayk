#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "unit_utils.h"
#include "game_clock.h"
#include "gameplay.h"

struct Player create_player(char player_name[MAXNAME])
{
    struct Player player;

    strcpy(player.player_name, player_name);
    player.health = MAXHEALTH;
    player.damage = MINDAMAGE;
    player.armor = MINARMOR;
    player.current_location = NULL;

    return player;
}

Game_Command_Type identify_game_command(const char *command)
{
    if (strcmp(command, "go") == 0) return GAME_MOVE;
    if (strcmp(command, "look") == 0) return GAME_LOOK;
    if (strcmp(command, "where") == 0) return GAME_WHERE;
    if (strcmp(command, "map") == 0) return GAME_MAP;
    if (strcmp(command, "quit") == 0) return GAME_QUIT;
    
    return GAME_UNKNOWN;
}

// Game_Command_Type parse_and_execute_command(const char *command)
// {
//     char *key = srttok(command, ' ');
//     Game_Command_Type command_type = identify_command(key[0]);
//     if(command_type == MOVE)
//     {

//     } else if(command_type == LOOK)
//     {

//     } else if(command_type == WHERE)
//     {

//     } else if(command_type == MAP)
//     {

//     } else if(command_type == QUIT)
//     {
//         return QUIT;
//     }
//     return UNKNOWN;
// }