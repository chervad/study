#pragma once

#include "cocos2d.h"

#include "defens.h"

using namespace cocos2d;

class HeroTank : public Sprite {
public:
	Animate * moveAnimate;

	static HeroTank *createWithSpriteFrame(SpriteFrame *spriteFrame);

	void move(int directionParam);

	void idle();

	void update();

private:
	~HeroTank();

	bool moving;

	int direction;

	void initPlayer();
};
