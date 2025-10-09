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

    Game_State game_state = STATE_MENU;

    struct Game_Clock game_clock = init_game_clock();
    struct Location *game_map = init_game_map();
    struct NPC *game_npc = init_game_npc(game_map);
    struct Player player = create_player();
    struct Game_Script_Manager game_script_manager = create_game_script_manager();

    printf("%s\n", load_game_title());
    getchar();

    while (game_state != STATE_QUIT)
    {
        if (game_state == STATE_MENU)
        {
            show_main_menu();
            printf("> ");
            if (fgets(buffer, MAXLINE, stdin))
            {
                int cmd = identify_main_menu_command(buffer);
                if (cmd == MENU_START)
                {
                    set_player_start_location(&player, game_map, game_map[0].game_map_size);
                    game_state = STATE_SCRIPT;
                }
                else if (cmd == MENU_QUIT)
                {
                    game_state = STATE_QUIT;
                }
                else
                {
                    game_state = STATE_MENU;
                }
                
            }
        }
        else if (game_state == STATE_SCRIPT)
        {
            run_game_script_manager(&game_script_manager);

            if (game_script_manager.script_command_type == SCRIPT_PAUSE)
            {
                game_state = STATE_PLAYING;
            }
            else
            {
                game_state = STATE_SCRIPT;
            }
        }
        else if (game_state == STATE_PLAYING)
        {
            show_command_menu();
            printf("> ");
            if (fgets(buffer, MAXLINE, stdin))
            {
                parse_and_execute_command(buffer, &player, game_map, game_map[0].game_map_size);

                if (player.game_command_type == GAME_MENU)
                {
                    game_state = STATE_MENU;
                }
                else
                {
                    game_state = STATE_PLAYING;
                }
            }
        }
        else
        {
            game_state = STATE_QUIT;
        }
    }

    free_game_npc(game_npc);
    free_game_map(game_map);

    return 0;
}