#pragma once

#include "cocos2d.h"
#include "defens.h"

using namespace cocos2d;

class Tank;

class Maze {
public:
	static Maze *create(uint16_t width, uint16_t height, Node *pParentNode);
	static bool moveTankThisPosition(Vec2 newPos, float width, float height, eDirection direction);
	~Maze();

	static void setMazePlan(Vec2 pos, char block);
	static char getMazePlan(Vec2 pos);
private:
	uint16_t width;
	uint16_t height;
	Node *pParentNode;
	bool isAutogenerate;

	//std::list<Wall *> listWall;
    void build();
};
