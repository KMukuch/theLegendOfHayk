#ifndef CONFIG_H
#define CONFIG_H

#define MAXNAME 50
#define MAXLINE 100

typedef enum
{
    DAY,
    NIGHT
} Day_Cycle_Type;

typedef enum {
    STATE_MENU,
    STATE_SCRIPT,
    STATE_PLAYING,
    STATE_QUIT
} Game_State;

typedef enum {
    MENU_UNKNOWN,
    MENU_START,
    MENU_LOAD,
    MENU_QUIT
} Menu_Command_Type;

typedef enum {
    SCRIPT_UNKNOWN,
    SCRIPT_LOAD,
    SCRIPT_PAUSE,
    SCRIPT_END
} Script_Command_Type;

typedef enum {
    GAME_UNKNOWN,
    GAME_GO,
    GAME_LOOK,
    GAME_WHERE,
    GAME_MAP_LOCAL,
    GAME_MAP_GLOBAL,
    GAME_MENU
} Game_Command_Type;

typedef enum {
    ITEM_UNKNOWN,
    ITEM_RANGE,
    ITEM_MELEE,
    ITEM_ARMOR
} Item_Type;

typedef enum {
    ITEM_BONUS_UNKNOWN,
    ITEM_BONUS_DAMAGE,
    ITEM_BONUS_ARMOR,
    ITEM_BONUS_HEALTH
} Item_Bonus_Type;

#endif