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
    struct Game_Script_Manager game_script_manager = create_game_script_manager();

    printf("%s\n", load_game_title());
    getchar();
    show_main_menu();
    fgets(buffer, MAXLINE, stdin);
    while(identify_main_menu_command(buffer) != MENU_QUIT)
    {
        if(identify_main_menu_command(buffer) == MENU_START)
        {
            set_player_start_location(&player, game_map, game_map[0].game_map_size);
            while(game_script_manager.script_command_type != SCRIPT_END)
            {
                run_game_script_manager(&game_script_manager);
                while(player.game_command_type != GAME_QUIT)
                {
                    fgets(buffer, MAXLINE, stdin);
                    parse_and_execute_command(buffer, &player);
                }
            }
        }
        fgets(buffer, MAXLINE, stdin);
    }

    free_game_npc(game_npc);
    free_game_map(game_map);

    return 0;
}