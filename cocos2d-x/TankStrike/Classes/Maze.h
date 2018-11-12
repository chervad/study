#pragma once

#include "cocos2d.h"
#include "defens.h"
#include "Wall.h"
#include "Tank.h"

using namespace cocos2d;

class Tank;

class Maze {
public:
	static Maze *create(uint16_t width, uint16_t height, Node *pParentNode);
	static bool moveTankThisPosition(Vec2 vpos, Tank::MoveDirection direct);
	~Maze();

	void build();
private:
	uint16_t width;
	uint16_t height;
	Node *pParentNode;
	bool isAutogenerate;

	std::list<Wall *> listWall;
};
