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
	//eDirection = MoveDirection::UP;
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

/*void PlayerTank::stopMove() {
	nX_delta = 0;
	nY_delta = 0;
	eDirection = MoveDirection::UP;
}*/

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

void PlayerTank::moveTo(MoveDirection direct) {
	moveTo(direct, DELTA);
}

void PlayerTank::moveTo(MoveDirection direct, int delta) {
	//eDirection = direct;
	if (direct == MoveDirection::LEFT || direct == MoveDirection::RIGHT) {
		nY_delta = 0;
	}
	if (direct == MoveDirection::UP || direct == MoveDirection::DOWN) {
		nX_delta = 0;
	}
	switch (direct) {
	case MoveDirection::LEFT:
		setRotation(-90.0f);
		nX_delta = -1 * delta;
		break;
	case MoveDirection::RIGHT:
		setRotation(90.0f);
		nX_delta = delta;
		break;
	case  MoveDirection::UP:
		setRotation(0.0f);
		nY_delta = delta;
		break;
	case  MoveDirection::DOWN:
		setRotation(180.0f);
		nY_delta = -1 * delta;
		break;
	}
}

/*void PlayerTank::moveTo(int deltaX, int deltaY)
{
	this->stopAllActions();
	this->runAction(RepeatForever::create(pMoveAnimate));
}*/

void PlayerTank::update(float dt)
{
	if (nX_delta != 0 || nY_delta != 0) {
		Point p = getPosition();
		Size size = Director::getInstance()->getWinSize();

		if (p.x + nX_delta > DELTA && p.x + nX_delta < size.width - DELTA &&
			p.y + nY_delta > DELTA && p.y + nY_delta < size.height - DELTA)
		{
			setPosition(Vec2(p.x + nX_delta, p.y + nY_delta));
		}
		//runMoveAnimate();
		if (pMoveAnimate->getTarget() != nullptr) {
			getActionManager()->resumeTarget(this);
		}
		else {
			runAction(RepeatForever::create(pMoveAnimate));
		}
	}
	if (nX_delta == 0 && nY_delta == 0) {
		//stopMoveAnimate();
		getActionManager()->pauseTarget(this);
	}
}