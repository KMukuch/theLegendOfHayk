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
    UNKNOWN,
    START,
    NEW,
    LOAD,
    MOVE,
    LOOK,
    WHERE,
    MAP,
    QUIT
} CommandType;

#endif