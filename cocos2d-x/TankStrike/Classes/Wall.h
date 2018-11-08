#pragma once

#include "cocos2d.h"

#include "defens.h"

using namespace cocos2d;

class Wall : public Sprite {
public:
	static Wall *create();
	~Wall();
protected:
	void initObject();
};
