#include <stdio.h>
#include <string.h>
#include "config.h"
#include "input_utils.h"
#include "menu.h"

void show_main_menu()
{
    printf("\n=== Main menu ===\n");
    printf("start\n");
    printf("load\n");
    printf("quit\n");
}

void show_command_menu()
{
    printf("\n=== Commands ===\n");
    printf("go [node] — go to the next node\n");
    printf("look — get a description of your current location\n");
    printf("where — show your current location\n");
    printf("map local — show local map\n");
    printf("map global — show global map\n");
    printf("menu — back to menu\n");
}

Menu_Command_Type identify_main_menu_command(const char *command)
{
    char trimmed_command[MAXLINE];
    strtrim(trimmed_command, command);

    if (strcmp(trimmed_command, "start") == 0) return MENU_START;
    if (strcmp(trimmed_command, "load") == 0) return MENU_LOAD;
    if (strcmp(trimmed_command, "quit") == 0) return MENU_QUIT;
    
    return MENU_UNKNOWN;
}