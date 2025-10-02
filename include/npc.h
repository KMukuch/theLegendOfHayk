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
char* json_get_dialogue(char *npc_name, const int id);

#endif