#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <stdio.h>
#include "config.h"
#include "unit_utils.h"
#include "game_map.h"
#include "game_npc.h"

#define MAXHEALTH 100
#define MINDAMAGE 5
#define MINARMOR 1
#define MAXITEM 20

struct Item
{
    char item_name[MAXNAME];
    Item_Type item_type;
};

struct Player_Location
{
    struct Map *map;
    struct Location *location;
};

struct Player
{
    // char player_name[MAXNAME];
    int health;
    int damage;
    int armor;
    struct Player_Location player_location;
    struct Item inventory[MAXITEM];
    Game_Command_Type game_command_type;
};

struct Player create_player();
void set_player_start_location(struct Player *player, const struct Maps *game_maps);

Game_Command_Type identify_game_command(const char *command);
void parse_and_execute_command(const char *command, struct Player *player, const struct Maps *game_maps, const struct NPCs *game_npcs);

void handle_go_command(const char *command, struct Player *player, const struct Maps *game_maps, const struct NPCs *game_npcs);
// void inspect_object();
// void attack_enemy();
// void show_status();
// void show_inventory();
// void save_game();
// void load_game();

#endif