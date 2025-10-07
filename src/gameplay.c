#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "input_utils.h"
#include "unit_utils.h"
#include "game_clock.h"
#include "gameplay.h"

struct Player create_player()
{
    struct Player player;

    player.health = MAXHEALTH;
    player.damage = MINDAMAGE;
    player.armor = MINARMOR;
    player.current_location = NULL;
    player.game_command_type = GAME_UNKNOWN;

    return player;
}

void set_player_start_location(struct Player *player, struct Location *game_map, int game_map_size)
{
    for(int i = 0; i < game_map_size; i++)
    {
        if(game_map[i].start_flag)
        {
            player->current_location = &game_map[i];
        }
    }
}

Game_Command_Type identify_game_command(const char *command)
{
    char trimmed_command[MAXLINE];
    strtrim(trimmed_command, command);

    if (strcmp(trimmed_command, "go") == 0) return GAME_GO;
    if (strcmp(trimmed_command, "look") == 0) return GAME_LOOK;
    if (strcmp(trimmed_command, "where") == 0) return GAME_WHERE;
    if (strcmp(trimmed_command, "map") == 0) return GAME_MAP;
    if (strcmp(trimmed_command, "menu") == 0) return GAME_MENU;
    
    return GAME_UNKNOWN;
}

void parse_and_execute_command(const char *command, struct Player *player)
{
    Game_Command_Type command_type = identify_game_command(command);
    player->game_command_type = command_type;
    if(command_type == GAME_WHERE)
    {
        printf("Your current location: %s", player->current_location->location_name);
    }
}