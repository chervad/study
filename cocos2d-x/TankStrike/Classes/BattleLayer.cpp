#include <thread>
#include <chrono>

#include "BattleLayer.h"
#include "SimpleAudioEngine.h"

#include "defens.h"

#include "Wall.h"
#include "Brick.h"

using namespace cocos2d;

//https://github.com/war1oc/cocos2d-x-player/tree/master/Classes

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
	listener->onKeyPressed = CC_CALLBACK_2(BattleLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(BattleLayer::onKeyReleased, this);

	auto contactListener = EventListenerPhysicsContact::create();
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

	this->scheduleUpdate();

	mainGameLoop();

    return true;
}

void BattleLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	pPlayerTank->onKeyPressed(keyCode, event);
}

void BattleLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	pPlayerTank->onKeyReleased(keyCode, event);

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
}

void BattleLayer::addEnemyTank(EnemyTank *pEnemyTank) {
	addChild(pEnemyTank);
	listEnemyTanks.push_back(pEnemyTank);
}

void BattleLayer::addEnemyBase(Vec2 position) {
	enemyBase.push_back(position); 
}

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

/*void BattleLayer::mainGameLoopProxy(BattleLayer *ptr) {
	ptr->mainGameLoop();
}*/

void BattleLayer::mainGameLoop() {
	//std::this_thread::sleep_for(std::chrono::seconds{ 3 });
	log("Ta-da!");
	for (const auto & base_pos : enemyBase) {
		EnemyTank *pEnemyTank = EnemyTank::create(pMaze);
		pEnemyTank->setPosition(base_pos);
		addEnemyTank(pEnemyTank);
		pEnemyTank->startGameLoop();
	}
}
