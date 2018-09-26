#pragma once

#include "cocos2d.h"

#include "defens.h"

using namespace cocos2d;

class PlayerTank : public Sprite {
public:
	static PlayerTank *create();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void moveTo(int deltaX, int deltaY);

	void idle();

	void update();

private:
	int nX_delta;
	int nY_delta;

	Animate *moveAnimate;

	~PlayerTank();
	void initHeroTank();
};
