#include "BattleLayer.h"
#include "PlayerTank.h"
#include "TextureFactory.h"
#include "Shot.h"
#include "EnemyTank.h"

PlayerTank::~PlayerTank()
{
	CC_SAFE_RELEASE(pMoveAnimate);
}

PlayerTank *PlayerTank::create()
{
	PlayerTank *playerTank = new PlayerTank();
	if (playerTank && playerTank->initWithSpriteFrame(TextureFactory::getInstance().getPlayerTankSprite()))
	{
		//playerTank->autorelease();
		playerTank->initTank();
		playerTank->initPhysics();
		playerTank->getPhysicsBody()->setContactTestBitmask(ObjType::PLAYER);
		return playerTank;
	}

	CC_SAFE_DELETE(playerTank);
	return NULL;
}

void PlayerTank::initTank()
{
	Tank::initTank();
	//pMoveAnimate = TextureFactory::getInstance().getPlayerTankAnimate();
	pMoveAnimate = TextureFactory::getInstance().getAnimate(ObjType::PLAYER);
	nX_delta = 0;
	nY_delta = 0;
	direction = eDirection::UP;
	life = 250.f;
	damage_koef = 1.25f;
}

void PlayerTank::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW: 
		moveTo(eDirection::LEFT);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		moveTo(eDirection::RIGHT);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		moveTo(eDirection::UP);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		moveTo(eDirection::DOWN);
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		Shot *pShot = Shot::create(direction, this->getPosition());
		BattleLayer *parent = (BattleLayer *)(this->getParent());
		parent->addShot(pShot);
		break;
	}
	this->playAnimation();
}

void PlayerTank::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	/*if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{*/
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
	/*}*/
	this->pauseAnimation();
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

void PlayerTank::calcParams() {
	
}
