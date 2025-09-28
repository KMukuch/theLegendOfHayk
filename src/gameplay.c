#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "utils.h"
#include "game_clock.h"
#include "gameplay.h"

struct Player create_player()
{
    struct Player player;

    player.curren_location = NULL;
    player.health = MAXHEALTH;

    return player;
}

CommandType identify_command(const char *command)
{
    if (strcmp(command, "go") == 0) return MOVE;
    if (strcmp(command, "look") == 0) return LOOK;
    if (strcmp(command, "where") == 0) return WHERE;
    if (strcmp(command, "map") == 0) return MAP;
    if (strcmp(command, "quit") == 0) return QUIT;
    
    return UNKNOWN;
}

CommandType parse_and_execute_command(const char *command)
{
    int keys[MAXKEY_NUMBER];

    char *key = srttok(command, ' ');
    CommandType command_type = identify_command(key[0]);
    if(command_type == MOVE)
    {

    } else if(command_type == LOOK)
    {

    } else if(command_type == WHERE)
    {

    } else if(command_type == MAP)
    {

    } else if(command_type == QUIT)
    {
        return QUIT;
    }
    return UNKNOWN;
}