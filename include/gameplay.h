#ifndef GAMEPLAY.H
#define GAMEPLAY.H

#include <stdio.h>
#include "config.h"
#include "utils.h"

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
// void parse_and_execute_command();
// void move_player();
// void inspect_object();
// void attack_enemy();
// void show_status();
// void show_inventory();
// void save_game();
// void load_game();
// void print_current_location();

#endif