#include "BattleScene.h"
#include "SimpleAudioEngine.h"

#include "defens.h"

using namespace cocos2d;

//https://github.com/war1oc/cocos2d-x-player/tree/master/Classes

BattleScene::BattleScene()
	: pTextures(nullptr)
	, pPlayerTank(nullptr)
	, pTank(nullptr)
{}

BattleScene::~BattleScene() {}

Scene* BattleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BattleScene::create(); //��� ���������� ����������� ����� � ����� �� ����� init �����
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

	Size size = Director::getInstance()->getWinSize();

	this->pTextures = Director::getInstance()->getTextureCache()->addImage("res/sprites/tiles.png");
	Rect rect = Rect::ZERO;
	rect.size = this->pTextures->getContentSize();
	this->tileWidth = rect.size.width / 22;
	this->tileHeight = rect.size.height / 12;

	this->pPlayerTank = PlayerTank::create();
	this->pPlayerTank->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(this->pPlayerTank);

	this->pTank
		= Sprite::createWithSpriteFrame(SpriteFrame::createWithTexture(this->pTextures
			, Rect(17 * this->tileWidth, 4 * this->tileHeight, this->tileWidth, this->tileHeight)));
	this->pTank->setPosition(Vec2(100, 100));
	this->addChild(this->pTank);

	this->scheduleUpdate();

    return true;
}

void BattleScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	log("Key with keycode %d pressed", keyCode);
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
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		Vec2 curPos = this->pTank->getPosition();
		float minX = -1 * curPos.x;
		float maxX = 640 - curPos.x;
		float minY = -1 * curPos.y;
		float maxY = 480 - curPos.y;
		this->pTank->runAction(MoveBy::create(2.0f, Vec2(random<float>(minX, maxX), random<float>(minY, maxY))));
	}
	/*if (this->nX_delta == 0 && this->nY_delta == 0) {
		this->pPlayerTank->getActionManager()->pauseTarget(this->pPlayerTank);
	}*/
}

void BattleScene::update(float dt) {
	/*if (this->nX_delta != 0 || this->nY_delta != 0) {
		Point p = this->pPlayerTank->getPosition();
		Size size = Director::getInstance()->getWinSize();

		if (p.x + this->nX_delta > DELTA && p.x + this->nX_delta < size.width - DELTA &&
			p.y + this->nY_delta > DELTA && p.y + this->nY_delta < size.height - DELTA)
		{
			this->pPlayerTank->setPosition(Vec2(p.x + this->nX_delta, p.y + this->nY_delta));
		}
	}*/
}
