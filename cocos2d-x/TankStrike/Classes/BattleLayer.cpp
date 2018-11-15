#include "BattleLayer.h"
#include "SimpleAudioEngine.h"

#include "defens.h"

#include "Wall.h"
#include "Brick.h"

using namespace cocos2d;

//https://github.com/war1oc/cocos2d-x-player/tree/master/Classes

BattleLayer::BattleLayer()
	: pPlayerTank(nullptr)
	, pEnemyTank(nullptr)
	, pMaze(nullptr)
	, br(nullptr)
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

	PhysicsWorld* world = scene->getPhysicsWorld();
	world->setGravity(Vec2(.0f, .0f));  
	//world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    return scene;
}

bool BattleLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
	auto listener = EventListenerKeyboard::create();
	/*listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
		log("Key with keycode %d pressed", keyCode);
	};*/
	listener->onKeyPressed = CC_CALLBACK_2(BattleLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(BattleLayer::onKeyReleased, this);

	auto contactListener = EventListenerPhysicsContact::create();
	/*contactListener->onContactBegin = [this](PhysicsContact &contact) {
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
		}
		return false;
	};*/
	contactListener->onContactBegin = CC_CALLBACK_1(BattleLayer::onContactBegin, this);

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

	this->pEnemyTank = EnemyTank::create();
	this->pEnemyTank->setPosition(EnemyTank::convertArea2Pos(10, 10));
	this->addChild(this->pEnemyTank);

	this->scheduleUpdate();

    return true;
}

void BattleLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	//log("Key with keycode %d pressed", keyCode);
	pPlayerTank->onKeyPressed(keyCode, event);
	/*if (this->nX_delta != 0 || this->nY_delta != 0) {
		if (this->pTankHeroMove->getTarget() != nullptr) {
			this->pTankHero->getActionManager()->resumeTarget(this->pTankHero);
		}
		else {
			this->pTankHero->runAction(RepeatForever::create(this->pTankHeroMove));
		}
	}*/
}

void BattleLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	//log("Key with keycode %d released", keyCode);	
	pPlayerTank->onKeyReleased(keyCode, event);
	/*if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		Vec2 curPos = this->pEnemyTank->getPosition();
		float minX = -1 * curPos.x;
		float maxX = 640 - curPos.x;
		float minY = -1 * curPos.y;
		float maxY = 480 - curPos.y;
		this->pEnemyTank->runAction(MoveBy::create(2.0f, Vec2(random<float>(minX, maxX), random<float>(minY, maxY))));
	}*/
	/*if (this->nX_delta == 0 && this->nY_delta == 0) {
		this->pPlayerTank->getActionManager()->pauseTarget(this->pPlayerTank);
	}*/
}

bool BattleLayer::onContactBegin(PhysicsContact &contact) 
{
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
	}
	return false;
}

void BattleLayer::addShot(Shot *pShot) { 
	addChild(pShot); 
	listShots.push_back(pShot); 

	/*Brick *pBrick = Brick::create(2, 5, 5);
	getParent()->addChild(pBrick);
	pBrick->setPosition(EnemyTank::convertArea2Pos(5, 5));*/
}

void BattleLayer::update(float dt) {
	pPlayerTank->update(dt);
	pEnemyTank->update(dt);
	for (auto pShot : listShots) {
		pShot->update(dt);
	}
	/*if (this->nX_delta != 0 || this->nY_delta != 0) {
		Point p = this->pPlayerTank->getPosition();
		Size sceneSize = Director::getInstance()->getWinSize();

		if (p.x + this->nX_delta > DELTA && p.x + this->nX_delta < sceneSize.width - DELTA &&
			p.y + this->nY_delta > DELTA && p.y + this->nY_delta < sceneSize.height - DELTA)
		{
			this->pPlayerTank->setPosition(Vec2(p.x + this->nX_delta, p.y + this->nY_delta));
		}
	}*/
}
