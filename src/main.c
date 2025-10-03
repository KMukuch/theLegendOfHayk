#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "game_menu.h"
#include "game_map.h"
#include "game_clock.h"
#include "game_script.h"
#include "gameplay.h"
#include "npc.h"

int main()
{
    char buffer[MAXLINE];

    struct Game_Clock game_clock = init_game_clock();
    struct Location *game_map = init_game_map();
    struct NPC *game_npc = init_game_npc(game_map);
    struct Player player = create_player();

    printf("%s\n", load_game_title());
    getchar();
    show_main_menu();
    fgets(buffer, MAXLINE, stdin);
    while(identify_menu_command(buffer) != MENU_QUIT)
    {
        if(identify_menu_command(buffer) == MENU_START)
        {
            printf("%s\n", load_game_openning_script());
        }
        fgets(buffer, MAXLINE, stdin);
    }
    
    // fgets(buffer, MAXLINE, stdin);
    // while(identify_command(buffer) != QUIT)
    // {
    //     if(identify_command(buffer) == START)
    //     {
    //         printf("Start the game");
    //     }
    // }

    free_game_npc(game_npc);
    free_game_map(game_map);

    return 0;
}