#ifndef GAME_CLOCK_H
#define GAME_CLOCK_H

#include <stdio.h>
#include "config.h"
#include "utils.h"

struct Game_Clock 
{
    float total_game_time;
    int current_day;
    float current_hour;
    Day_Cycle_Type day_cycle_type;
};

struct Game_Clock init_game_clock();
struct Game_Clock* advance_game_clock(struct Game_Clock *game_clock, const float hours);
int get_current_day(const struct Game_Clock *game_clock);
// float get_current_hour();
// char* get_current_hour_as_string();
// Day_Cycle_Type get_current_day_cycle_type();

#endif