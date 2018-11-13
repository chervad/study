#include "PlayerTank.h"

#include "TextureFactory.h"

PlayerTank::~PlayerTank()
{
	CC_SAFE_RELEASE(pMoveAnimate);
}

PlayerTank *PlayerTank::create()
{
	PlayerTank *playerTank = new PlayerTank();
	if (playerTank && playerTank->initWithSpriteFrame(TextureFactory::getInstance().getPlayerTankSprite()))
	{
		playerTank->autorelease();
		playerTank->initTank();
		playerTank->initPhysics();
		return playerTank;
	}

	CC_SAFE_DELETE(playerTank);
	return NULL;
}

void PlayerTank::initTank()
{
	pMoveAnimate = TextureFactory::getInstance().getPlayerTankAnimate();
	nX_delta = 0;
	nY_delta = 0;
	eDirection = MoveDirection::UP;
}

void PlayerTank::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW: 
		moveTo(MoveDirection::LEFT); 
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		moveTo(MoveDirection::RIGHT); 
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		moveTo(MoveDirection::UP); 
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		moveTo(MoveDirection::DOWN); 
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		log("Piu-Piu!");
		break;
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

/*void PlayerTank::runMoveAnimate() {
	if (!pCurrentMoveAction) {
		stopAction(pCurrentMoveAction);
	}
	pCurrentMoveAction = runAction(RepeatForever::create(pMoveAnimate));
}*/

/*void PlayerTank::stopMoveAnimate() {
	if (!pCurrentMoveAction) {
		stopAction(pCurrentMoveAction);
	}
}*/
