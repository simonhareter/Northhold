CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = build/main

SRC = main.c \
      src/game.c \
      src/world.c \
      src/renderer.c \
      src/assets.c \
      src/camera.c \
      src/input.c \
	  src/menu.c \
	  src/settings.c \
	  src/cursor.c \
	  src/pause_menu.c \
	  src/button.c \
	  src/audio.c \
	  src/slider.c

OBJ = $(patsubst %.c,build/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

default: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

build/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

clean:
	rm -rf build

.PHONY: default clean

