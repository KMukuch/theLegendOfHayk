#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <stdio.h>
#include "menu.h"

void show_main_menu();
Menu_Command_Type identify_menu_command(const char *command);
// Menu_Command_Type parse_menu_command();

#endif