CC = clang
CFLAGS = -Iinclude -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lcjson
SRC = src/main.c src/input_utils.c src/json_utils.c src/game_menu.c src/game_clock.c src/game_map.c src/npc.c src/game_script.c src/gameplay.c

OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
TARGET = build/main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
	
build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -rf build