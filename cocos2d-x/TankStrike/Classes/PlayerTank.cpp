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
    PhysicsBody *physicsBody = PhysicsBody::createBox(Size(this->getContentSize().width - 4, this->getContentSize().height - 4));
    physicsBody->setDynamic(false);
    this->setPhysicsBody(physicsBody);
}

void PlayerTank::search(eDirection dir) {
	moveTo(dir);
    auto director = Director::getInstance();

    auto func = [](PhysicsWorld& world, PhysicsShape& shape, void* userData)->bool
    {
        int bitmask = shape.getContactTestBitmask();
        if (bitmask != ObjType::BRICK && bitmask != ObjType::WALL) {
            PlayerTank *playerTank = (PlayerTank *)userData;
            eDirection dir = playerTank->getDirection();
			switch (dir) {
			case eDirection::LEFT: playerTank->getPhysicsBody()->setVelocity(Vec2(-100.0f, .0f)); break;
			case eDirection::RIGHT: playerTank->getPhysicsBody()->setVelocity(Vec2(100.0f, .0f)); break;
			case eDirection::UP: playerTank->getPhysicsBody()->setVelocity(Vec2(.0f, 100.0f)); break;
			case eDirection::DOWN: playerTank->getPhysicsBody()->setVelocity(Vec2(.0f, -100.0f)); break;
			}
			log("move to %d", dir);
        }
        log("bitmask: %d", bitmask);
        return true;
    };
    PhysicsWorld* world = director->getRunningScene()->getPhysicsWorld();
    if (dir == eDirection::LEFT) {
        world->queryRect(func,
                Rect (this->getBoundingBox().getMinX() - this->width
                        , this->getBoundingBox().getMinY()
                        , this->getBoundingBox().size.width
                        , this->getBoundingBox().size.height),
                        this);
    } else if (dir == eDirection::RIGHT) {
        world->queryRect(func,
                         Rect (this->getBoundingBox().getMinX() + this->width
                                 , this->getBoundingBox().getMinY()
                                 , this->getBoundingBox().size.width
                                 , this->getBoundingBox().size.height),
                         this);
    } else if (dir == eDirection::UP) {
        world->queryRect(func,
                         Rect (this->getBoundingBox().getMinX()
                                 , this->getBoundingBox().getMinY() + this->height
                                 , this->getBoundingBox().size.width
                                 , this->getBoundingBox().size.height),
                         this);
    } else if (dir == eDirection::DOWN) {
        world->queryRect(func,
                         Rect (this->getBoundingBox().getMinX()
                                 , this->getBoundingBox().getMinY() - this->height
                                 , this->getBoundingBox().size.width
                                 , this->getBoundingBox().size.height),
                         this);
    }
}

void PlayerTank::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	    search(eDirection::LEFT);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		search(eDirection::RIGHT);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		search(eDirection::UP);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		search(eDirection::DOWN);
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
    this->getPhysicsBody()->setVelocity(Vec2(.0f, .0f));
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