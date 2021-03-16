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

void PlayerTank::update(float dt)
{
    if (nX_delta != 0 || nY_delta != 0) {
        Point curPos = this->getPosition();

        if (curPos.x + nX_delta > DELTA && curPos.x + nX_delta < winSize.width - DELTA &&
            curPos.y + nY_delta > DELTA && curPos.y + nY_delta < winSize.height - DELTA)
        {
			int collisions = 0;
            Vec2 newPos = Vec2(curPos.x + nX_delta, curPos.y + nY_delta);

			auto director = Director::getInstance();

			auto func = [](PhysicsWorld& world, PhysicsShape& shape, void* userData)->bool
			{
				int collisions = *((int *)userData);
				//Return true from the callback to continue rect queries
				int bitmask = shape.getContactTestBitmask();
				if (bitmask != ObjType::PLAYER && bitmask != ObjType::GROUND) {
					log("new pos %d (%.2f, %.2f)", bitmask, shape.getBody()->getPosition().x, shape.getBody()->getPosition().y);
					collisions++;
				}
				return false;
			};
			//log("pos old(%.2f, %.2f) -> new(%.2f, %.2f)", curPos.x, curPos.y, newPos.x, newPos.y);
			//Rect rc = this->getBoundingBox();
			//Rect rc_new(rc.getMinX() + nX_delta, rc.getMinY() + nY_delta, rc.size.width, rc.size.height);
			Rect rc_new(newPos.x - this->width, newPos.y - this->height, 2*this->width, 2*this->height);

			/*auto rectNode = DrawNode::create();
			Color4F white(1, 1, 1, 0.15);
			rectNode->drawRect(Vec2(rc_new.getMinX(), rc_new.getMinY()), Vec2(rc_new.getMaxX(), rc_new.getMaxY()), white);
			this->getParent()->addChild(rectNode);*/

			//log("box (%.2f, %.2f, %.2f, %.2f)", rc_new.getMinX(), rc_new.getMinY(), rc_new.getMaxX(), rc_new.getMaxY());
			//PhysicsWorld* world = director->getRunningScene()->getPhysicsWorld();
			//world->queryRect(func, rc_new, &collisions);
			//log("collisions %d", collisions);
            if (Maze::moveTankThisPosition(newPos, this->width, this->height, this->direction)) {
                this->setPosition(newPos);

                std::tuple<uint16_t, uint16_t> post = EnemyTank::convertPos2Area(newPos);
                this->posX = std::get<0>(post);
                this->posY = 19 - std::get<1>(post) - 1;
            }
			
            //Rect bbox = this->getBoundingBox();
            //log("%.2f, %.2f, %.2f, %.2f", bbox.getMinX(), bbox.getMinY(), bbox.size.width, bbox.size.height);
            //Rect newBbox = Rect(bbox.getMinX())
        }
        //log("update");
    }
}
