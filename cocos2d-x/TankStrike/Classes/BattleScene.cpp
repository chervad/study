#include "BattleScene.h"
#include "SimpleAudioEngine.h"

#include "defens.h"

#include "Wall.h"

using namespace cocos2d;

//https://github.com/war1oc/cocos2d-x-player/tree/master/Classes

BattleScene::BattleScene()
	: pPlayerTank(nullptr)
	, pEnemyTank(nullptr)
	, pMaze(nullptr)
{}

BattleScene::~BattleScene() {
	CC_SAFE_DELETE(this->pPlayerTank);
	CC_SAFE_DELETE(this->pEnemyTank);
	CC_SAFE_DELETE(this->pMaze);
}

Scene* BattleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BattleScene::create(); //тут вызывается конструктор сцены и сразу же метод init сцены
	scene->addChild(layer);
    return scene;
}

bool BattleScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
	auto listener = EventListenerKeyboard::create();
	/*listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
		log("Key with keycode %d pressed", keyCode);
	};*/
	listener->onKeyPressed = CC_CALLBACK_2(BattleScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(BattleScene::onKeyReleased, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

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
	this->pPlayerTank->setPosition(Vec2(sceneSize.width / 2, sceneSize.height / 2));
	this->addChild(this->pPlayerTank);

	this->pEnemyTank = EnemyTank::create();
	this->pEnemyTank->setPosition(EnemyTank::convertArea2Pos(10, 10));
	this->addChild(this->pEnemyTank);


	this->scheduleUpdate();

    return true;
}

void BattleScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	log("Key with keycode %d pressed", keyCode);
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

void BattleScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	log("Key with keycode %d released", keyCode);	
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

void BattleScene::update(float dt) {
	pPlayerTank->update(dt);
	pEnemyTank->update(dt);
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
