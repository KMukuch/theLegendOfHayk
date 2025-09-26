#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "utils.h"
#include "game_clock.h"

struct Game_Clock init_game_clock()
{
    struct Game_Clock game_clock;

    game_clock.total_game_time = 0.0;
    game_clock.current_day = 1;
    game_clock.current_hour = 6.0;
    game_clock.day_cycle_type = DAY;

    return game_clock;
}

struct Game_Clock* advance_game_clock(struct Game_Clock *game_clock, const float hours)
{
    game_clock->total_game_time += hours;
    game_clock->current_day = floor(game_clock->total_game_time / 24.0f);
    game_clock->current_hour = game_clock->total_game_time - 24 * game_clock->current_day;

    return game_clock;
}

int get_current_day(const struct Game_Clock *game_clock)
{
    return game_clock->current_day;
}