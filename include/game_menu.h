#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <stdio.h>
#include "menu.h"

void show_main_menu();
void show_command_menu();
// void show_dialogue_menu();
Menu_Command_Type identify_main_menu_command(const char *command);

#endif