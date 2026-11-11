#ifndef CAMERA_H
#define CAMERA_H

#include "config.h"
#include "world.h"
#include <raylib.h>

#define CAMERA_SPEED    750.0F
#define CAMERA_TARGET   ((Vector2){WORLD_WIDTH * TILE_SIZE / 2.0F, WORLD_HEIGHT * TILE_SIZE / 2.0F})
#define CAMERA_OFFSET   ((Vector2){SCREEN_WIDTH / 2.0F, SCREEN_HEIGHT / 2.0F})
#define CAMERA_ROTATION 0.0F
#define CAMERA_ZOOM     1.5F

void move_camera(Camera2D *camera, KeyboardKey dir);
void init_camera(Camera2D *camera);

#endif
