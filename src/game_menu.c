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

Menu_Command_Type identify_menu_command(const char *command)
{
    char trimmed_command[MAXLINE];
    strtrim(trimmed_command, command);

    if (strcmp(trimmed_command, "start") == 0) return MENU_START;
    if (strcmp(trimmed_command, "look") == 0) return MENU_LOAD;
    if (strcmp(trimmed_command, "quit") == 0) return MENU_QUIT;
    
    return MENU_UNKNOWN;
}

// Menu_Command_Type parse_menu_command()
// {
//     Menu_Command_Type menu_command = UNKNOWN;

//     if(menu_command == MOVE)
//     {

//     } else if(menu_command == LOOK)
//     {

//     } else if(menu_command == WHERE)
//     {

//     } else if(menu_command == MAP)
//     {

//     } else if(menu_command == QUIT)
//     {
//         return QUIT;
//     }
//     return menu_command;
// }