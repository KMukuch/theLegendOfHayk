#ifndef CONFIG_H
#define CONFIG_H

#define MAXNAME 50
#define FILENAME "../data/game_map.json"

typedef enum 
{
    DEFAULT,
    REGION,
    CITY,
    VILLAGE,
    PLACE
} Location_Type;

typedef enum
{
    DAY,
    NIGHT
} Day_Cycle_Type;

#endif