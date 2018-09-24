#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

HelloWorld::HelloWorld() 
	: pTextures(nullptr)
	, pTankHero(nullptr)
	, pTankHeroMoveAnimation(nullptr)
	, pTank(nullptr)
	, createAnimate(false)
	, nX_delta(0)
	, nY_delta(0)
{
	log("4");
}

HelloWorld::~HelloWorld() {}

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create(); //��� ���������� ����������� ����� � ����� �� ����� init �����
	scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }
	auto listener = EventListenerKeyboard::create();
	/*listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
		log("Key with keycode %d pressed", keyCode);
	};*/
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	Size size = Director::getInstance()->getWinSize();

	this->pTextures = Director::getInstance()->getTextureCache()->addImage("res/sprites/tiles.png");
	Rect rect = Rect::ZERO;
	rect.size = this->pTextures->getContentSize();
	this->tileWidth = rect.size.width / 22;
	this->tileHeight = rect.size.height / 12;
	this->pTankHero
		= Sprite::createWithSpriteFrame(SpriteFrame::createWithTexture(this->pTextures, Rect(14 * this->tileWidth, 0 * this->tileHeight, this->tileWidth, this->tileHeight)));
	this->pTankHero->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(this->pTankHero);

	this->pTank
		= Sprite::createWithSpriteFrame(SpriteFrame::createWithTexture(this->pTextures, Rect(17 * this->tileWidth, 4 * this->tileHeight, this->tileWidth, this->tileHeight)));
	this->pTank->setPosition(Vec2(100, 100));
	this->addChild(this->pTank);

	this->loadObjects();

	this->scheduleUpdate();

    return true;
}

void HelloWorld::loadObjects() {
	this->pTankHeroMoveAnimation = Animation::create();
	this->fillAnimatation(this->pTankHeroMoveAnimation);
	this->pTankHeroMoveAnimation->setDelayPerUnit(0.1f);
	this->pTankHeroMoveAnimation->setRestoreOriginalFrame(true);
	this->pTankHeroMoveAnimation->setLoops(-1);
	this->pTankHero->getActionManager()->addAction(Animate::create(this->pTankHeroMoveAnimation), this->pTankHero, true);
}

void HelloWorld::fillAnimatation(Animation *animation) {
	for (int i = 0; i < 8; i++) {
		Rect rect = Rect((14 + i) * this->tileWidth, 0 * this->tileHeight, this->tileWidth, this->tileHeight);
		SpriteFrame *frame = SpriteFrame::createWithTexture(this->pTextures, rect);
		animation->addSpriteFrame(frame);
	}
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
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
		/*if (!this->createAnimate) {
			auto animation = Animation::create();
			//for (int i = 1; i <= 8; i++) {
			//	std::string name = StringUtils::format("res/sprites/tank_%02d_top.png", i);
			//	animation->addSpriteFrameWithFile(name.c_str());
			//}
			this->fillAnimatation(animation);
			animation->setDelayPerUnit(0.1f);
			animation->setRestoreOriginalFrame(true);
			animation->setLoops(-1);
			auto animate = Animate::create(animation);
			this->pTankHero->runAction(animate);
			this->createAnimate = true;
		}
		else {
			this->pTankHero->getActionManager()->resumeTarget(this->pTankHero);
		}*/
		this->pTankHero->getActionManager()->resumeTarget(this->pTankHero);
	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
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
	}
	if (this->nX_delta == 0 && this->nY_delta == 0) {
		this->pTankHero->getActionManager()->pauseTarget(this->pTankHero);
	}
}

void HelloWorld::update(float dt) {
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
