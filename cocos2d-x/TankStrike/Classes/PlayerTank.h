#pragma once

#include "cocos2d.h"

#include "defens.h"
#include "Tank.h"

using namespace cocos2d;

class PlayerTank : public Tank {
public:
	static PlayerTank *create();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	//void stopMove();
	//void moveTo(int deltaX, int deltaY);
	virtual ~PlayerTank() override;

	void update(float dt) override;
protected:
	void initTank();
	//void runMoveAnimate();
	//void stopMoveAnimate();
};
