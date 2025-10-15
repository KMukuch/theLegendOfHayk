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
    player.player_location.map = NULL;
    player.player_location.location = NULL;
    player.game_command_type = GAME_UNKNOWN;

    return player;
}

void set_player_start_location(struct Player *player, const struct Maps *game_maps)
{
    for (int i = 0; i < game_maps->map_array_size; i++)
    {
        struct Map *map = &game_maps->map_array[i];
        for (int j = 0; j < map->location_array_size; j++)
        {
            if (map->location_array[j].start_flag)
            {
                player->player_location.map = map;
                player->player_location.location = &map->location_array[j];
            }
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
    if (strcmp(trimmed_command, "map local") == 0) return GAME_MAP_LOCAL;
    if (strcmp(trimmed_command, "map global") == 0) return GAME_MAP_GLOBAL;
    if (strcmp(trimmed_command, "menu") == 0) return GAME_MENU;
    
    return GAME_UNKNOWN;
}

void parse_and_execute_command(const char *command, struct Player *player, const struct Maps *game_maps)
{
    Game_Command_Type command_type = identify_game_command(command);
    player->game_command_type = command_type;
    if(command_type == GAME_MAP_GLOBAL)
    {
        for(int i = 0; i < game_maps->map_array_size; i++)
        {
            printf("%s\n", game_maps->map_array[i].map_name);
            for(int j = 0; j < game_maps->map_array[i].map_connection_array_size; j++)
            {
                printf("->%s\n", game_maps->map_array[i].map_connection_array[j].map->map_name);
            }
        }
    } else if(command_type == GAME_WHERE)
    {
        printf("Your current location: %s, %s", player->player_location.map->map_name, player->player_location.location->location_name);
    }
}