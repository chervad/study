#pragma once

#include "cocos2d.h"

#include "defens.h"

#include "Wall.h"

using namespace cocos2d;

class Maze {
public:
	static Maze *create(uint16_t width, uint16_t height, Node *pParentNode);
	~Maze();

	void build();
private:
	uint16_t width;
	uint16_t height;
	Node *pParentNode;

	std::list<Wall *> listWall;
};
