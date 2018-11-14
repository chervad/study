#pragma once

#define WIDTH 640
#define HEIGHT 480

#define DELTA 1

enum class ObjType : uint16_t {
	PLAYER,
	ENEMY,
	WALL,
	BRICK,
	GROUND,
	EAGLE,
	SHOT
};

enum class MoveDirection {
	LEFT,
	RIGHT,
	UP,
	DOWN
};
