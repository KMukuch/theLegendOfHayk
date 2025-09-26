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
    if (!game_map) 
    {
        fprintf(stderr, "Failed to initialize game map\n");
        return 1;
    }

    printf("game_map_size = %d\n", game_map[0].game_map_size);
    printf("total game time %f, current day %i, current hour %f, %i\n", game_clock.total_game_time, game_clock.current_day, game_clock.current_hour, game_clock.day_cycle_type);
    
    for (int i = 0; i < game_map[0].game_map_size; i++) 
    {
        printf("%s connections:\n", game_map[i].location_name);
        for (int j = 0; j < game_map[i].connections_count; j++) 
        {
            printf("  -> %s (distance=%d)\n", game_map[i].connections[j].location->location_name, game_map[i].connections[j].connection_distance);
        }
    }

    for (int i = 0; i < game_map[0].game_map_size; i++) 
    {
        free(game_map[i].connections);
    }
    free(game_map);

    return 0;
}