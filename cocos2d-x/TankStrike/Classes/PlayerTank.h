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

	virtual ~PlayerTank() override;

	void update(float dt) override;
protected:
	void initTank();
	void initPhysics() override;
	void search(eDirection dir);
	//void runMoveAnimate();
	//void stopMoveAnimate();
private:
    uint8_t unposibleDir_; //bitmask
};
