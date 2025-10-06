#include <stdio.h>
#include <string.h>
#include "config.h"
#include "input_utils.h"
#include "menu.h"

void show_main_menu()
{
    printf("=== Main Menu ===\n");
    printf("1. Start Game\n");
    printf("2. Load Game\n");
    printf("3. Quit\n");
}

// void show_command_options()
// {
//     printf("=== Command Options ===\n");
//     printf("1. go [node] — go to the next node");
//     printf("2. look — get a description of your current location\n");
//     printf("3. where — show your current location\n");
//     printf("4. map — show your current location on the global map\n");
// }

// void show_dialogue_menu()
// {
//     printf("=== Dualogue Menu ===\n");
//     printf("1. Continue");
//     printf("2. Quit\n");
// }

Menu_Command_Type identify_main_menu_command(const char *command)
{
    char trimmed_command[MAXLINE];
    strtrim(trimmed_command, command);

    if (strcmp(trimmed_command, "start") == 0) return MENU_START;
    if (strcmp(trimmed_command, "look") == 0) return MENU_LOAD;
    if (strcmp(trimmed_command, "quit") == 0) return MENU_QUIT;
    
    return MENU_UNKNOWN;
}