#pragma once

#include "cocos2d.h"

#include "defens.h"

using namespace cocos2d;

class PlayerTank : public Sprite {
public:
	enum class MoveDirection {
		LEFT, 
		RIGHT,
		UP, 
		DOWN
	};
public:
	static PlayerTank *create();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void update(float dt);

	//void stopMove();
	void moveTo(MoveDirection direct);
	void moveTo(MoveDirection direct, int delta);
	//void moveTo(int deltaX, int deltaY);

private:
	int nX_delta;
	int nY_delta;
	//MoveDirection eDirection;

	Animate *pMoveAnimate;

	~PlayerTank();

	void initTank();

	//void runMoveAnimate();
	//void stopMoveAnimate();
};
