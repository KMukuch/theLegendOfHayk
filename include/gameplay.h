#ifndef GAMEPLAY.H
#define GAMEPLAY.H

#include <stdio.h>
#include "config.h"
#include "utils.h"

#define MAXHEALTH 100
#define MAXLINE 100

struct Player
{
    struct Location *current_location;
    int health;
};

struct Item
{
    char item_name[MAXNAME];
};

struct Player create_player();
CommandType identify_command(const char *command);
void parse_and_execute_command(char *command);
// void move_player();
// void inspect_object();
// void attack_enemy();
// void show_status();
// void show_inventory();
// void save_game();
// void load_game();
// void print_current_location();

#endif