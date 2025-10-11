#ifndef NPC_H
#define NPC_H

#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "game_map.h"

struct NPC 
{
    char npc_name[MAXNAME];
    const struct Location *current_location;
    bool flag;
    int dialogue_id;
};

struct NPC create_npc(const char *npc_name);
int get_game_npc_size();
struct NPC* init_game_npc(const struct Maps *game_maps);
void free_game_npc(struct NPC *game_npc);
char* json_get_dialogue(char *npc_name, const int id);
void free_dialogue_content(char *dialogue_content);

#endif