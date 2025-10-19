#ifndef GAME_NPC_H
#define GAME_NPC_H

#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "game_map.h"

struct NPC_Location
{
    struct Map *map;
    struct Location *location;
};

struct NPC 
{
    char npc_name[MAXNAME];
    struct NPC_Location npc_location;
    bool flag;
    int dialogue_id;
};

struct NPCs
{
    struct NPC *npc_array;
    int npc_array_size;
};

struct NPC create_npc(const char *npc_name);
struct NPCs init_game_npcs(const struct Maps *game_maps);
void free_game_npcs(struct NPCs *npcs);
char* json_get_dialogue(char *npc_name, const int id);
void free_dialogue_content(char *dialogue_content);

#endif