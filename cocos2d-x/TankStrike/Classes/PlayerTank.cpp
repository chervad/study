#include "BattleLayer.h"
#include "PlayerTank.h"
#include "TextureFactory.h"
#include "Shot.h"

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
}

void PlayerTank::initPhysics() {
    //PhysicsBody *physicsBody = PhysicsBody::createBox(this->getBoundingBox().size);
    PhysicsBody *physicsBody = PhysicsBody::createBox(Size(this->getContentSize().width - DELTA_PH, this->getContentSize().height - DELTA_PH));
    physicsBody->setDynamic(false);
    this->setPhysicsBody(physicsBody);
}

bool PlayerTank::checkMove() {
    auto director = Director::getInstance();

    PhysicsWorld* world = director->getRunningScene()->getPhysicsWorld();
    float minX = this->getBoundingBox().getMinX();
    float maxX = this->getBoundingBox().getMaxX();
    float minY = this->getBoundingBox().getMinY();
    float maxY = this->getBoundingBox().getMaxY();
    if (this->direction == eDirection::LEFT) {
        Vector<PhysicsShape*> shapesVectot1 = world->getShapes(Vec2(minX - DELTA_MV, minY + DELTA_PH));
        Vector<PhysicsShape*> shapesVectot2 = world->getShapes(Vec2(minX - DELTA_MV, maxY - DELTA_PH));
        if (shapesVectot1.empty() && shapesVectot2.empty()) {
            return true;
        }
    } else if (this->direction == eDirection::RIGHT) {
        Vector<PhysicsShape*> shapesVectot1 = world->getShapes(Vec2(maxX + DELTA_MV, minY + DELTA_PH));
        Vector<PhysicsShape*> shapesVectot2 = world->getShapes(Vec2(maxX + DELTA_MV, maxY - DELTA_PH));
        if (shapesVectot1.empty() && shapesVectot2.empty()) {
            return true;
        }
    } else if (this->direction == eDirection::UP) {
        Vector<PhysicsShape*> shapesVectot1 = world->getShapes(Vec2(minX + DELTA_PH, maxY + DELTA_MV));
        Vector<PhysicsShape*> shapesVectot2 = world->getShapes(Vec2(maxX - DELTA_PH, maxY + DELTA_MV));
        if (shapesVectot1.empty() && shapesVectot2.empty()) {
            return true;
        }
    } else if (this->direction == eDirection::DOWN) {
        Vector<PhysicsShape*> shapesVectot1 = world->getShapes(Vec2(minX + DELTA_PH, minY - DELTA_MV));
        Vector<PhysicsShape*> shapesVectot2 = world->getShapes(Vec2(maxX - DELTA_PH, minY - DELTA_MV));
        if (shapesVectot1.empty() && shapesVectot2.empty()) {
            return true;
        }
    }
    return false;
}

void PlayerTank::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    PhysicsBody* body = this->getPhysicsBody();
    switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        moveTo(eDirection::LEFT);
	    if (checkMove()) body->setVelocity(Vec2(-100.0f, .0f));
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        moveTo(eDirection::RIGHT);
        if (checkMove()) body->setVelocity( Vec2(100.0f, .0f));
        break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
        moveTo(eDirection::UP);
        if (checkMove()) body->setVelocity(Vec2(.0f, 100.0f));
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        moveTo(eDirection::DOWN);
        if (checkMove()) body->setVelocity(Vec2(.0f, -100.0f));
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
    if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
        keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW ||
        keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
        keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
    {
        this->getPhysicsBody()->setVelocity(Vec2(.0f, .0f));
    }
	this->pauseAnimation();
}

void PlayerTank::update(float dt)
{
    /*if (nX_delta != 0 || nY_delta != 0) {
        Point curPos = this->getPosition();

        if (curPos.x + nX_delta > DELTA && curPos.x + nX_delta < winSize.width - DELTA &&
            curPos.y + nY_delta > DELTA && curPos.y + nY_delta < winSize.height - DELTA)
        {
            Vec2 newPos = Vec2(curPos.x + nX_delta, curPos.y + nY_delta);
			Rect rc_new(newPos.x - this->width, newPos.y - this->height, 2*this->width, 2*this->height);

			if (Maze::moveTankThisPosition(newPos, this->width, this->height, this->direction)) {
				this->setPosition(newPos);
            }
        }
    }*/
}

/*void PlayerTank::runMoveAnimate() {
	if (!pCurrentMoveAction) {
		stopAction(pCurrentMoveAction);
	}
	pCurrentMoveAction = runAction(RepeatForever::create(pMoveAnimate));
}

void PlayerTank::stopMoveAnimate() {
	if (!pCurrentMoveAction) {
		stopAction(pCurrentMoveAction);
	}
}*/