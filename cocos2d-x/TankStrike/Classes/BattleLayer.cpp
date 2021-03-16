#include <thread>
#include <chrono>

#include "BattleLayer.h"
#include "SimpleAudioEngine.h"

#include "defens.h"

#include "Wall.h"
#include "Brick.h"
#include "Ground.h"

using namespace cocos2d;

//https://github.com/war1oc/cocos2d-x-player/tree/master/Classes
//https://habr.com/ru/company/ruvds/blog/451870/
//https://docs.cocos2d-x.org/api-ref/cplusplus/V3.17/d9/d66/classcocos2d_1_1_event_listener_physics_contact.html#a644614522bde93c371f44d42eb5c52ea

BattleLayer::BattleLayer()
	: pPlayerTank(nullptr)
	, pMaze(nullptr)
{}

BattleLayer::~BattleLayer() {
	/*CC_SAFE_DELETE(this->pPlayerTank);
	CC_SAFE_DELETE(this->pEnemyTank);
	CC_SAFE_DELETE(this->pMaze);*/
}

Scene* BattleLayer::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = BattleLayer::create(); //тут вызывается конструктор сцены и сразу же метод init сцены
	scene->addChild(layer);

	/*PhysicsWorld* world = scene->getPhysicsWorld();
	world->setGravity(Vec2(.0f, .0f));  
	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_CONTACT);// DEBUGDRAW_ALL);*/

    return scene;
}

bool BattleLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(BattleLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(BattleLayer::onKeyReleased, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(BattleLayer::onContactBegin, this);
	//contactListener->onContactPreSolve = CC_CALLBACK_2(BattleLayer::onContactPreSolve, this);
	//contactListener->onContactSeparate = CC_CALLBACK_1(BattleLayer::onContactSeparate, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	/*auto startlabel = LabelTTF::create("[$200]", "Courier New.ttf", 51);
	const ccMenuCallback& callback = [](Object *obj) {
		log("item1 touched");
	};
	auto item1 = MenuItemLabel::create(startlabel, callback);
	Menu *menu = Menu::create(item1, NULL);
	menu->alignItemsHorizontallyWithPadding(10);
	addChild(menu);*/
	Size sceneSize = Director::getInstance()->getWinSize();
	std::tuple<uint16_t, uint16_t> max_pos = EnemyTank::convertPos2Area(Vec2(sceneSize.width, sceneSize.height));

	this->pMaze = Maze::create(std::get<0>(max_pos), std::get<1>(max_pos) + 1, this);

	this->pPlayerTank = PlayerTank::create();
	this->pPlayerTank->setPosition(Vec2(sceneSize.width / 2, (sceneSize.height / 2) + 2));
	this->addChild(this->pPlayerTank);

	for (const auto & base_pos : enemyBase) {
        EnemyTank *pEnemyTank = EnemyTank::create();
        pEnemyTank->setPosition(base_pos);
        addEnemyTank(pEnemyTank);
    }
	this->scheduleUpdate();

    return true;
}

void BattleLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	pPlayerTank->onKeyPressed(keyCode, event);
}

void BattleLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	pPlayerTank->onKeyReleased(keyCode, event);

}

bool BattleLayer::onContactBegin(PhysicsContact &contact) {
	PhysicsShape *shapeA = contact.getShapeA();
	PhysicsBody *bodyA = shapeA->getBody();

	PhysicsShape *shapeB = contact.getShapeB();
	PhysicsBody *bodyB = shapeB->getBody();

	int resMask = bodyA->getContactTestBitmask() | bodyB->getContactTestBitmask();

	if (resMask == (ObjType::SHOT | ObjType::WALL)
		|| resMask == (ObjType::SHOT | ObjType::BRICK))
	{
		Shot *pShot = (Shot *)(bodyA->getContactTestBitmask() == ObjType::SHOT ? bodyA->getNode() : bodyB->getNode());
		listShots.remove(pShot);
		pShot->Boom();

		if (resMask & ObjType::BRICK) {
			Brick *pBrick = (Brick *)(bodyA->getContactTestBitmask() == ObjType::BRICK ? bodyA->getNode() : bodyB->getNode());
			pBrick->Blast();
		}
		return true;
	} /*else if (resMask == (ObjType::PLAYER | ObjType::WALL)
               || resMask == (ObjType::PLAYER | ObjType::BRICK))
	{
		PlayerTank *pTank = nullptr;
		ObjType objType;
		Vec2 tankPos;
		Vec2 hardlePos;
		if (bodyA->getContactTestBitmask() == ObjType::PLAYER) {
			pTank = (PlayerTank *)bodyA->getNode();
			objType = (ObjType)bodyB->getContactTestBitmask();
			tankPos = pTank->getPosition();
			hardlePos = bodyB->getNode()->getPosition();
			pTank->stop();
            //log("player tank");
			pTank = (PlayerTank *)bodyB->getNode();
			objType = (ObjType)bodyA->getContactTestBitmask();
			tankPos = pTank->getPosition();
			hardlePos = bodyA->getNode()->getPosition();
			pTank->stop();
			//log("player tank");
		}
		if (tankPos.x > hardlePos.x) {
			pTank->setNearbyObj(eDirection::LEFT, objType);
		}
		else if (tankPos.x < hardlePos.x) {
			pTank->setNearbyObj(eDirection::RIGHT, objType);
		}
		if (tankPos.y > hardlePos.y) {
			pTank->setNearbyObj(eDirection::DOWN, objType);
		}
		else if (tankPos.y < hardlePos.y) {
			pTank->setNearbyObj(eDirection::UP, objType);
		}
		//log("contact %s, %d", pTank->printNearbyObj().c_str(), bodyA->getContactTestBitmask());
		return true;
	}*/
	/*else {
        if (resMask == (ObjType::GROUND | ObjType::ENEMY)) {
            EnemyTank *pEnemyTank = (EnemyTank *)(bodyA->getContactTestBitmask() == ObjType::ENEMY ? bodyA->getNode() : bodyB->getNode());
            Ground *pGround = (Ground *)(bodyB->getContactTestBitmask() == ObjType::GROUND ? bodyB->getNode() : bodyA->getNode());
            std::tuple<uint16_t, uint16_t> areaPos = EnemyTank::convertPos2Area(pGround->getPosition());
            log("Enemy tank on %u:%u", std::get<0>(areaPos), std::get<1>(areaPos));
            return true;
        } else if (resMask == (ObjType::GROUND | ObjType::PLAYER)) {
			PlayerTank *pPlayerTank = (PlayerTank *)(bodyA->getContactTestBitmask() == ObjType::PLAYER ? bodyA->getNode() : bodyB->getNode());
			Ground *pGround = (Ground *)(bodyB->getContactTestBitmask() == ObjType::GROUND ? bodyB->getNode() : bodyA->getNode());
			std::tuple<uint16_t, uint16_t> areaPos = EnemyTank::convertPos2Area(pGround->getPosition());
			log("Player tank on %u:%u", std::get<0>(areaPos), std::get<1>(areaPos));
			return true;
		}
	}*/
    //log("mask %d", resMask);
	return false;
}

void BattleLayer::addShot(Shot *pShot) {
	std::lock_guard<std::mutex> guard(guard_mutex);
	addChild(pShot); 
	listShots.push_back(pShot); 
}

void BattleLayer::addEnemyTank(EnemyTank *pEnemyTank) {
	addChild(pEnemyTank);
	listEnemyTanks.push_back(pEnemyTank);
}

void BattleLayer::addEnemyBase(Vec2 position) {
	enemyBase.push_back(position); 
}

/*
PlayerTank *BattleLayer::getPlayerTank() const {
    return this->pPlayerTank;
}

void BattleLayer::update(float dt) {
	pPlayerTank->update(dt);
	for (auto pEnemyTank : listEnemyTanks) {
		pEnemyTank->update(dt);
	}
	for (auto pShot : listShots) {
		pShot->update(dt);
	}
}

void BattleLayer::onContactSeparate(PhysicsContact & contact)
{
	PhysicsShape *shapeA = contact.getShapeA();
	PhysicsBody *bodyA = shapeA->getBody();

	PhysicsShape *shapeB = contact.getShapeB();
	PhysicsBody *bodyB = shapeB->getBody();

	int resMask = bodyA->getContactTestBitmask() | bodyB->getContactTestBitmask();

	if (resMask == (ObjType::PLAYER | ObjType::WALL)
		|| resMask == (ObjType::PLAYER | ObjType::BRICK))
	{
		PlayerTank *pTank = nullptr;
		Vec2 tankPos;
		Vec2 hardlePos;
		if (bodyA->getContactTestBitmask() == ObjType::PLAYER) {
			pTank = (PlayerTank *)bodyA->getNode();
			tankPos = pTank->getPosition();
			hardlePos = bodyB->getNode()->getPosition();
		}
		else {
			pTank = (PlayerTank *)bodyB->getNode();
			tankPos = pTank->getPosition();
			hardlePos = bodyA->getNode()->getPosition();
		}
		if (tankPos.x > hardlePos.x) {
			pTank->setNearbyObj(eDirection::LEFT, ObjType::GROUND);
		}
		else if (tankPos.x < hardlePos.x) {
			pTank->setNearbyObj(eDirection::RIGHT, ObjType::GROUND);
		}
		if (tankPos.y > hardlePos.y) {
			pTank->setNearbyObj(eDirection::DOWN, ObjType::GROUND);
		}
		else if (tankPos.y < hardlePos.y) {
			pTank->setNearbyObj(eDirection::UP, ObjType::GROUND);
		}
		//log("separate %s", pTank->printNearbyObj().c_str());
	}
}

bool BattleLayer::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve) {
    PhysicsShape *shapeA = contact.getShapeA();
    PhysicsBody *bodyA = shapeA->getBody();

    PhysicsShape *shapeB = contact.getShapeB();
    PhysicsBody *bodyB = shapeB->getBody();

    int resMask = bodyA->getContactTestBitmask() | bodyB->getContactTestBitmask();

    if (resMask == (ObjType::PLAYER | ObjType::WALL) || resMask == (ObjType::PLAYER | ObjType::BRICK))
    {
        PlayerTank *pTank = nullptr;
        if (bodyA->getContactTestBitmask() == ObjType::PLAYER) {
            pTank = (PlayerTank *)bodyA->getNode();
        } else {
            pTank = (PlayerTank *)bodyB->getNode();
        }
        if (pTank != nullptr) {
            pTank->stop();
        }
        log("player tank");
        return true;
    }
    return false;
}*/
