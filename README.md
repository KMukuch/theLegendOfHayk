# The Legend of Hayk

**The Legend of Hayk** is a text-based adventure game written in **C**. The game immerses players in a narrative inspired by the legend of Hayk, where choices and exploration shape the journey. Players navigate through quests, encounter challenges, and interact with the story world - all through a command-line interface.

## Table of contents

- [Project Structure](#project-structure)
- [Features](#features)
- [Installation](#installation)
- [Gameplay](#gameplay)
- [Contributing](#contributing)
- [License](#license)

## Project Structure

- src
- include
- docs
- data
- build
- README

## Features

The game is designed to give a time experience of the real world. With each player interaction, the game clock moves forward. NPCs move, items appear or disappear, and locations evolve over time.

### In-game unit system

1. Time Standard
    - Unit: 1 in-game hour (H)
    - The basic measure of all time-related events
    - Day/night cycles:
        - Day: 12 H
        - Night: 12 H

2. Distance Standard
    - Unit: 1 in-game distance (D)
    - The basic measure of all distance-related events, a distance between two adjacent locations
    - 1 D = 1 H

3. Action Standard
    - Unit: 1 in-game action (A)
    - Only command `inspect [object/npc/place]` can be measured
    - 1 A = 1/6 H

## Installation



## World / Maps

### Regional Map

- Assiria
    - Babylon (City)
    - Nippur (City)

- Babylon
    - Assiria
    - Van

- Nippur
    - Assiria
    - Babylon

- Van
    - Babylon (City)
    - Ararat
    - Tushpa (City)

- Ararat
    - Van
    - Sevan

- Sevan
    - Ararat
    - Caucasus

- Caucasus
    - Sevan
    - Mtskheta (City)

### World Map

- Babylon
    - Nippur
    - Van

- Nippur
    - Tushpa
    - Babylon

- Tushpa (Lake Van)
    - Nippur
    - Mount Ararat

- Mount Ararat
    - Sevan

- Sevan
    - Mtskheta

- Mtskheta
    - Sevan

### Babylon

- City Gate (South)
    - Main Road

- Main Road
    - City Gate (South)
    - Marketplace
    - Palace District
    - Temple of Marduk

- Marketplace
    - Main Road
    - Residential Quarter

- Residential Quarter
    - Marketplace
    - Inner Gardens

- Inner Gardens
    - Residential Quarter
    - Palace District

- Palace District
    - Main Road
    - Inner Gardens
    - Ziggurat

- Temple of Marduk
    - Main Road
    - Ziggurat

- Ziggurat (Etemenanki)
    - Palace District
    - Temple of Marduk

### Nippur

- City Gate (North)
    - Main Street

- Main Street
    - City Gate (North)
    - Temple of Enlil
    - Marketplace
    - Residential Quarter

- Temple of Enlil
    - Main Street
    - Ziggurat

- Marketplace
    - Main Street
    - Residential Quarter

- Residential Quarter
    - Marketplace
    - Inner Gardens

- Inner Gardens
    - Residential Quarter
    - Temple of Enlil

- Ziggurat
    - Temple of Enlil

### Tushpa

- City Gate (Main Entrance)
    - Main Street

- Main Street
    - City Gate (Main Entrance)
    - Marketplace
    - Royal Fortress
    - Temple of Haldi

- Marketplace
    - Main Street
    - Residential Quarter

- Residential Quarter
    - Marketplace
    - Inner Gardens (optional)

- Inner Gardens
    - Residential Quarter
    - Royal Fortress

- Royal Fortress
    - Main Street
    - Inner Gardens
    - Watchtower

- Temple of Haldi
    - Main Street
    - Watchtower

- Watchtower
    - Royal Fortress
    - Temple of Haldi
    
### Mtskheta

- City Gate (East)
    - Main Street

- Main Street
    - City Gate (East)
    - Royal Citadel
    - Temple District
    - Market Square

- Royal Citadel
    - Main Street

- Temple District
    - Main Street
    - Market Square

- Market Square
    - Main Street
    - Temple District
    
### Village Map

- [Village Name]
    - Main Street
    - Marketplace
    - Residential Quarter
    - Watchtower
    - Outpost Gate

- Main Street
    - Marketplace
    - Residential Quarter

- Marketplace
    - Main Street
    - Residential Quarter
    - Watchtower

- Residential Quarter
    - Main Street
    - Marketplace
    - Outpost Gate

- Watchtower
    - Marketplace
    - Outpost Gate

- Outpost Gate
    - Residential Quarter
    - Watchtower

## Gameplay

### Movement & Exploration

- `go [direction]` — Move north, south, east, west, up, down
- `look` — Describe the current location
- `where` — Show your current location
- `map` — (Optional) Show map coordinates or info

### Interaction

- `inspect [object/npc/place]` — Examine details  
- `talk [npc]` — Start dialogue
- `take [item]` — Pick up an item
- `drop [item]` — Leave an item
- `use [item]` — Use an item
- `open [door/chest]` — Open a container or path
- `close [door/chest]` — Close a container or path

### Combat & Survival

- `attack [enemy]` — Engage in combat
- `block` — Defend against attacks
- `dodge` — Evade an attack
- `flee` — Attempt to run away
- `equip [item]` — Equip a weapon or armor
- `unequip [item]` — Unequip a weapon or armor

### Inventory & Status

- `inventory (inv)` — List items carried
- `stats` — Show health, energy, and other stats
- `quests` — Show active or completed quests
- `skills` — Show learned abilities

### Roleplay & Story

- `say [message]` — Speak to nearby NPCs
- `rest / camp` — Restore energy or health

### Meta / Utility

- `help` — List available commands  
- `save` — Save game progress  
- `load` — Load game progress  
- `quit` — Exit the game

## Contributing



## License

This project is licensed under the MIT License. See LICENSE.txt for details.
[LICENSE.txt](LICENSE.txt)
