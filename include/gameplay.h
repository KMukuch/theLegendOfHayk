#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <stdio.h>
#include "config.h"
#include "unit_utils.h"

#define MAXHEALTH 100
#define MINDAMAGE 5
#define MINARMOR 1
#define MAXITEM 20

struct Player
{
    char player_name[MAXNAME];
    int health;
    int damage;
    int armor;
    struct Location *current_location;
    struct Item inventory[MAXITEM];
};

struct Item
{
    Item_Type item_type;
    char item_name[MAXNAME];
};

struct Player create_player(char player_name[MAXNAME]);
Game_Command_Type identify_game_command(const char *command);
// void parse_and_execute_command(char *command);
// void move_player();
// void inspect_object();
// void attack_enemy();
// void show_status();
// void show_inventory();
// void save_game();
// void load_game();
// void print_current_location();

#endif