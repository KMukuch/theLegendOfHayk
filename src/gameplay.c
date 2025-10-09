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
    if (strcmp(trimmed_command, "map local") == 0) return GAME_MAP_LOCAL;
    if (strcmp(trimmed_command, "map global") == 0) return GAME_MAP_GLOBAL;
    if (strcmp(trimmed_command, "menu") == 0) return GAME_MENU;
    
    return GAME_UNKNOWN;
}

void parse_and_execute_command(const char *command, struct Player *player, const struct Location *game_map, int game_map_size)
{
    Game_Command_Type command_type = identify_game_command(command);
    player->game_command_type = command_type;
    if(command_type == GAME_MAP_GLOBAL)
    {
        for(int i = 0; i < game_map_size; i++)
        {
            printf("%s\n", game_map[i].location_name);
            printf("Connections (%i)\n", game_map[i].connections_count);
            for(int j = 0; j < game_map[i].connections_count; j++)
            {
                printf("-> %s (distance: %d)\n", game_map[i].connections[j].location->location_name, game_map[i].connections[j].connection_distance);
            }
        }
    } else if(command_type == GAME_MAP_LOCAL)
    {
        for(int i = 0; i < game_map_size; i++)
        {
            if (game_map[i].local_map != NULL)
            {
                for (int k = 0; k < game_map[i].local_map_size; k++)
                {
                    printf("%s\n", game_map[i].local_map[k].location_name);
                    printf("Connections (%i):\n", game_map[i].local_map[k].connections_count);
                    for (int j = 0; j < game_map[i].local_map[k].connections_count; j++)
                    {
                        printf("-> %s (distance: %d)\n", 
                            game_map[i].local_map[k].connections[j].location->location_name, 
                            game_map[i].local_map[k].connections[j].connection_distance);
                    }
                }
            }
        }
    } else if(command_type == GAME_WHERE)
    {
        printf("Your current location: %s", player->current_location->location_name);
    }
}