#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "game_map.h"
#include "game_clock.h"

int main()
{
    struct Game_Clock game_clock = init_game_clock();

    struct Location *game_map = init_game_map();

    for (int i = 0; i < game_map[0].game_map_size; i++) 
    {
        free(game_map[i].connections);
    }
    free(game_map);

    return 0;
}