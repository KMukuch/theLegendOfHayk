# The Legend of Hayk

**The Legend of Hayk** is a text-based adventure game written in **C**. The game immerses players in a narrative inspired by the legend of Hayk. Players navigate through quests, encounter challenges, and interact with the story world - all through a command-line interface.

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

- Babylon

### Local Maps

#### Village

## Gameplay

### Movement & Exploration

- `go [node]` — go to the next node
- `look` — describe the current location
- `where` — show your current location
- `map global` — show global map
- `map local` — show local map
- `rest` — restore health

### Interaction

- `inspect [object/npc/place]` — examine details  
- `talk [npc]` — start dialogue
- `take [item]` — pick up an item
- `drop [item]` — leave an item
- `use [item]` — use an item

### Combat

- `attack [enemy]` — engage in combat
- `block` — defend against attacks
- `equip [item]` — equip a weapon or armor
- `unequip [item]` — unequip a weapon or armor

### Inventory & Status

- `inventory` — list items carried
- `stats` — show health, energy, and other stats
- `quests` — show active or completed quests
- `skills` — show learned abilities

### Help

- `help` — list available commands  
- `save` — save game progress  
- `load` — load game progress
- `menu` - enter the menu
- `quit` — exit the game

## Contributing



## License

This project is licensed under the MIT License. See LICENSE.txt for details.
[LICENSE.txt](LICENSE.txt)
