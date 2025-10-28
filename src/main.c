#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "game_menu.h"
#include "game_map.h"
#include "game_clock.h"
#include "game_script.h"
#include "game_npc.h"
#include "game_quest.h"
#include "gameplay.h"

int main()
{
    char buffer[MAXLINE];

    Game_State game_state = STATE_MENU;
    
    struct Game_Clock game_clock = init_game_clock();
    struct Maps game_maps = init_game_map();
    struct NPCs game_npcs = init_game_npcs(&game_maps);
    struct Player player = create_player();
    struct Game_Script_Manager game_script_manager = create_game_script_manager();
    struct Game_Quest_Manager game_quest_manager = create_game_quest_manager();
    
    init_game_quest_manager(&game_quest_manager, &game_maps);
    // read_game_quests(&game_quest_manager);

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
                    set_player_start_location(&player, &game_maps);
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
            struct Game_Quest_Reference game_quest_reference;

            run_game_script_manager(&game_script_manager);
            update_game_quest_manager(&game_quest_manager, &game_quest_reference);

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
                parse_and_execute_command(buffer, &player, &game_maps, &game_npcs);

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

    free_game_npcs(&game_npcs);
    free_game_quest_manager(&game_quest_manager)
    free_game_map(&game_maps);

    return 0;
}