# Overview

This project is a modular **C** program for a text-based game. The folowing document describes code's structure and game's logic.

## Table of contents

- [Overview](#overview)
- [Code Structure](#code-structure)
- [Libraries](#libraries)
- [Data Types and Data Structures](#data-types-and-data-structures)
- [Workflow](#Workflow)
- [JSON Files](#json-files)
- [In Development](#in-development)

## Code structure

The code is split into multiple files:

- 'main.c' - runs game's main loop;
- 'config.h' - contains generall constants and enums; 
- 'input_utils.h/c' - contains variables and functions for parsing input;
- 'json_utils.h/c' - contains variables and functions for parsing json files;
- 'game_menu.h/c' - contains game's menus;
- 'game_map.h/c' - contains variables and functions to initiate game's map and work with it;
- 'game_clock.h/c' - contains variables and functions to initiate game's clock and work with it;
- 'game_script.h/c' - contains variables and functions for parsing game's script json files;
- 'gameplay.h/c' - contains variables and functions to parse player's commands;
- 'game_npc.h/c' - contains variables and functions to initiate game's NPCs and parse their dialogues from json files.

## Libraries

- Standard C libraries: `stdio.h`, `stdlib.h`, `string.h`, `stdbool.h`
- Third-party: `cJSON` for JSON parsing

## Data types and data structures

### config.h

#### Constants

- `#define MAXNAME 50`, `#define MAXLINE 100` and `#define MAXDESCRIPTION 500` are the maximum number of characters to be used in names, user input and descriptions;

#### Enums

- `Game_State` enum is used to control the game flow. It has the folowing members:
    - `STATE_MENU` - used to access game's menu;
    - `STATE_SCRIPT` - used to access game's script;
    - `STATE_PLAYING` - used for user input (gaming);
    - `STATE_QUIT` - quits the game;

- `Menu_Command_Type` - enum is used to control the game's menu. It has the folowing members:
    - `MENU_UNKNOWN` - used when the command is unidentified;
    - `MENU_START` - used to start the game;
    - `MENU_LOAD` - used to load the game;
    - `MENU_QUIT` - quits the menu;

- `Script_Command_Type` enum is used to control script reading. It has the folowing members:
    - `SCRIPT_UNKNOWN` - 
    - `SCRPIT_LOAD` - used to load the script;
    - `SCRIPT_PAUSE` - stops reading and waits for user input;
    - `SCRIPT_END` - marks the end of the script and stops reading;
    
- `Game_Command_Type` enum is used to parse and identify user input. It has the folowing members:
    - `GAME_UKNNOWN` - used when the command is unidentified;
    - `GAME_GO` - used to move the player;
    - `GAME_LOOK` - 
    - `GAME_WHERE` - 
    - `GAME_MAP_LOKAL` -
    - `GAME_MAP_GLOBAL` - 
    - `GAME_MEUN` - shows menu;

- `Item_Type` enum is used to identify the items found in the game. It has the folowing members:
    - `ITEM_UKNOWN` - 
    - `ITEM_RANGE` - used to mark distance combat items;
    - `ITEM_MELEE` - used to mark close combat items;
    - `ITEM_ARMOR` - used to mark armor items;

- `Item_Bonus_Type` enum is used to identify item's bonus type. It has the folowing memebers:
    - `ITEM_BONUS_UNKNOWN` - 
    - `ITEM_BONUS_DAMAGE` - item increases atack damage;
    - `ITEM_ARMOR` - item increases armor;
    - `ITEM_HEALTH` - item increases health;

- `Game_Quest_Type` enum is used to identify the quest type. It has the folowing members:
    - `GAME_QUEST_UNKNOWN` - 
    - `GAME_QUEST_MAIN` - main story quests;
    - `GAME_QUEST_SIDE` - side quests;
    
- `Objective_Type` enum is used to identify the objective type. It has the folowing members:
    - `OBJECTIVE_UNKNOWN` - 
    - `OBJECTIVE_LOCATION` - in order to complete the objective the player has to go to a certain location;
    - `OBJECTIVE_NPC` - in order to complete the objective the player has to interact with an npc;
    - `OBJECTIVE_ITEM` - in order to complete the objective the player has to interact with a certain item;
    - `OBJECTIVE_ENEMY` - in order to complete the objective the player has to defeat an enemy;

### input_utils.h

### json_utils.h

### game_map.h

#### Structs

##### Maps

Struct `Maps` contains an array of struct `Map`.

```
struct Maps
{
    struct Map *map_array;
    int map_array_size;
};
```

Each element of the array represents a node from game_map.json file. Each map contains a reference to the correspondent .json file with map locations. The struct `Map_Connection` points to the adjacent members of the `map_array`.

```
struct Map
{
    char map_name[MAXNAME];
    char map_ref[MAXLINE];
    struct Map_Connection *map_connection_array;
    int map_connection_array_size;
    struct Location *location_array;
    int location_array_size;
};
```

Each `Map_Connection` then points to a map and contains the distance between the adjacent nodes.

```
struct Map_Connection 
{
    const struct Map *map;
    int connection_distance;
};
```

Map locations are stored in an array of struct `Location`. The struct `Location_Connection` points to the adjacent members of the `location_array`.

```
struct Location
{
    char location_name[MAXNAME];
    bool start_flag;
    struct Location_Connection *connection_array;
    int location_connection_array_size;
};
```

Each `Location_Connection` then points to a location and contains the distance between the adjacent nodes.

```
struct Location_Connection 
{
    const struct Location *location;
    int connection_distance;
};
```

### game_quest.h

#### Structs

```
struct Game_Quest_Manager
{
    struct Game_Quest *game_quest_array;
    int game_quest_array_size;
};
```

## Workflow

## JSON Files

## In development

- Inventory system
- Quest system
- NPC AI and behavior
- Additional locations and maps
