#ifndef CAMERA_H
#define CAMERA_H

#include <raylib.h>

#define CAMERA_SPEED 750.0f

void move_camera(Camera2D *camera, KeyboardKey dir);

#endif
