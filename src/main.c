#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "game_map.h"

int main()
{
    struct Location *game_map = init_game_map();

    printf("game_map_size = %d\n", game_map[0].game_map_size);

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

    return 0;
}