#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <stdio.h>
#include "config.h"
#include "unit_utils.h"
#include "game_map.h"

#define MAXHEALTH 100
#define MINDAMAGE 5
#define MINARMOR 1
#define MAXITEM 20

struct Item
{
    Item_Type item_type;
    char item_name[MAXNAME];
};

struct Player
{
    // char player_name[MAXNAME];
    int health;
    int damage;
    int armor;
    struct Location *current_location;
    struct Item inventory[MAXITEM];
    Game_Command_Type game_command_type;
};

struct Player create_player();
Game_Command_Type identify_game_command(const char *command);
void set_player_start_location(struct Player *player, struct Location *game_map, int game_map_size);
Game_Command_Type identify_game_command(const char *command);
void parse_and_execute_command(const char *command, struct Player *player);
// void move_player(struct Player *player);
// void inspect_object();
// void attack_enemy();
// void show_status();
// void show_inventory();
// void save_game();
// void load_game();

#endif