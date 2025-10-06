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
    MENU_UNKNOWN,
    MENU_START,
    MENU_LOAD,
    MENU_QUIT
} Menu_Command_Type;

typedef enum {
    SCRIPT_UNKNOWN,
    SCRIPT_LOAD,
    SCRIPT_END
} Script_Command_Type;

typedef enum {
    GAME_UNKNOWN,
    GAME_GO,
    GAME_LOOK,
    GAME_WHERE,
    GAME_MAP,
    GAME_QUIT
} Game_Command_Type;

typedef enum {
    ITEM_UNKNOWN,
    ITEM_DAMAGE,
    ITEM_ARMOR,
    ITEM_HEALTH
} Item_Type;

#endif