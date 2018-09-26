#include "PlayerTank.h"

#include "TextureFactory.h"

PlayerTank::~PlayerTank()
{
	CC_SAFE_RELEASE(moveAnimate);
}

PlayerTank *PlayerTank::create()
{
	PlayerTank *heroTank = new PlayerTank();
	if (heroTank && heroTank->initWithSpriteFrame(TextureFactory::getInstance().getPlayerTankSprite()))
	{
		heroTank->autorelease();
		heroTank->initHeroTank();
		return heroTank;
	}

	CC_SAFE_DELETE(heroTank);
	return NULL;
}

void PlayerTank::initHeroTank()
{
	moveAnimate = TextureFactory::getInstance().getPlayerTankAnimate();
}

void PlayerTank::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			nY_delta = 0;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			nX_delta = 0;
		}
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			setRotation(-90.0f);
			nX_delta = -DELTA;

			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			setRotation(90.0f);
			nX_delta = DELTA;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			setRotation(0.0f);
			nY_delta = DELTA;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			setRotation(180.0f);
			nY_delta = -DELTA;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			log("Piu-Piu!");
			break;
		}
	}
}

void PlayerTank::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			nX_delta = 0;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			nY_delta = 0;
		}
	}
}

void PlayerTank::moveTo(int deltaX, int deltaY)
{
	this->stopAllActions();
	this->runAction(RepeatForever::create(moveAnimate));
}

void PlayerTank::idle()
{
	this->stopAllActions();
	//this->runAction(RepeatForever::create(idleAnimate));
}

void PlayerTank::update()
{
	/*if (moving) //check if moving
	{
		if (direction == 0) //check if going left
		{
			this->setScaleX(-1); //flip
			this->setPositionX(this->getPositionX() - 5);
		}
		else
		{
			this->setScaleX(1); //flip
			this->setPositionX(this->getPositionX() + 5);
		}
	}*/
}