#pragma once

#define WIDTH 640
#define HEIGHT 480

#define DELTA 1

enum ObjType {
	GROUND,
	PLAYER = 0b00000001,
	ENEMY  = 0b00000010,
	WALL   = 0b00000100,
	BRICK  = 0b00001000,
	EAGLE  = 0b00100000,
	SHOT   = 0b01000000
};

enum class MoveDirection {
	LEFT,
	RIGHT,
	UP,
	DOWN
};
