#include "BattleScene.h"
#include "SimpleAudioEngine.h"

#include "defens.h"

#include "HeroTank.h"

using namespace cocos2d;

//https://github.com/war1oc/cocos2d-x-player/tree/master/Classes

BattleScene::BattleScene()
	: pTextures(nullptr)
	, pTankHero(nullptr)
	, pTankHeroMove(nullptr)
	, pTank(nullptr)
	, createAnimate(false)
	, nX_delta(0)
	, nY_delta(0)
{}

BattleScene::~BattleScene() {}

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

	Size size = Director::getInstance()->getWinSize();

	this->pTextures = Director::getInstance()->getTextureCache()->addImage("res/sprites/tiles.png");
	Rect rect = Rect::ZERO;
	rect.size = this->pTextures->getContentSize();
	this->tileWidth = rect.size.width / 22;
	this->tileHeight = rect.size.height / 12;

	this->pTankHero
		= HeroTank::createWithSpriteFrame(SpriteFrame::createWithTexture(this->pTextures, Rect(14 * this->tileWidth, 0 * this->tileHeight, this->tileWidth, this->tileHeight)));
	this->pTankHero->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(this->pTankHero);

	this->pTank
		= Sprite::createWithSpriteFrame(SpriteFrame::createWithTexture(this->pTextures
			, Rect(17 * this->tileWidth, 4 * this->tileHeight, this->tileWidth, this->tileHeight)));
	this->pTank->setPosition(Vec2(100, 100));
	this->addChild(this->pTank);

	auto tankHeroAnimation = Animation::create();
	this->fillAnimatation(tankHeroAnimation);
	tankHeroAnimation->setDelayPerUnit(0.1f);
	tankHeroAnimation->setRestoreOriginalFrame(true);
	tankHeroAnimation->setLoops(-1);
	this->pTankHeroMove = Animate::create(tankHeroAnimation);
	this->pTankHeroMove->retain();

	this->scheduleUpdate();

    return true;
}

void BattleScene::fillAnimatation(Animation *animation) {
	for (int i = 0; i < 8; i++) {
		Rect rect = Rect((14 + i) * this->tileWidth, 0 * this->tileHeight, this->tileWidth, this->tileHeight);
		SpriteFrame *frame = SpriteFrame::createWithTexture(this->pTextures, rect);
		animation->addSpriteFrame(frame);
	}
}

void BattleScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	log("Key with keycode %d pressed", keyCode);
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || 
		keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || 
		keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			this->nY_delta = 0;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) 
		{
			this->nX_delta = 0;
		}
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			this->pTankHero->setRotation(-90.0f);
			this->nX_delta = -DELTA;

			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			this->pTankHero->setRotation(90.0f);
			this->nX_delta = DELTA;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			this->pTankHero->setRotation(0.0f);
			this->nY_delta = DELTA;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			this->pTankHero->setRotation(180.0f);
			this->nY_delta = -DELTA;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			log("Piu-Piu!");
			break;
		}
	}
	if (this->nX_delta != 0 || this->nY_delta != 0) {
		if (this->pTankHeroMove->getTarget() != nullptr) {
			this->pTankHero->getActionManager()->resumeTarget(this->pTankHero);
		}
		else {
			this->pTankHero->runAction(RepeatForever::create(this->pTankHeroMove));
		}
	}
}

void BattleScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	log("Key with keycode %d released", keyCode);

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			this->nX_delta = 0;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			this->nY_delta = 0;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
			Vec2 curPos = this->pTank->getPosition();
			float minX = -1 * curPos.x;
			float maxX = 640 - curPos.x;
			float minY = -1 * curPos.y;
			float maxY = 480 - curPos.y;
			this->pTank->runAction(MoveBy::create(2.0f, Vec2(random<float>(minX, maxX), random<float>(minY, maxY))));
		}
	}
	if (this->nX_delta == 0 && this->nY_delta == 0) {
		this->pTankHero->getActionManager()->pauseTarget(this->pTankHero);
	}
}

void BattleScene::update(float dt) {
	if (this->nX_delta != 0 || this->nY_delta != 0) {
		Point p = this->pTankHero->getPosition();
		Size size = Director::getInstance()->getWinSize();

		if (p.x + this->nX_delta > DELTA && p.x + this->nX_delta < size.width - DELTA &&
			p.y + this->nY_delta > DELTA && p.y + this->nY_delta < size.height - DELTA)
		{
			this->pTankHero->setPosition(Vec2(p.x + this->nX_delta, p.y + this->nY_delta));
		}
	}
}
