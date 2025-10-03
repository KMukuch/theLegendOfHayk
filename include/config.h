#ifndef CONFIG_H
#define CONFIG_H

#define MAXNAME 50

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

typedef enum {
    MENU_UNKNOWN,
    MENU_START,
    MENU_LOAD,
    MENU_QUIT
} Menu_Command_Type;

typedef enum {
    GAME_UNKNOWN,
    GAME_MOVE,
    GAME_LOOK,
    GAME_WHERE,
    GAME_MAP,
    GAME_QUIT
} Game_Command_Type;

#endif