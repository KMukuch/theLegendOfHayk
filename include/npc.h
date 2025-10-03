#ifndef NPC_H
#define NPC_H

#include <stdio.h>
#include "config.h"

struct NPC 
{
    struct Location *current_location;
    bool flag;
};

struct NPC create_npc();
void set_npc_location(struct NPC *npc);
int get_npc_location(const struct NPC *npc);
void init_game_npc();
char* json_get_dialogue(char *npc_name, const int id);
void free_dialogue_content(char *dialogue_content);

#endif