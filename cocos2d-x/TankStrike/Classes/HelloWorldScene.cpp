#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

HelloWorld::HelloWorld() 
	: pTankHero(nullptr)
	, pAnimateMoveTrucks(nullptr)
	, nX_delta(0)
	, nY_delta(0)
	, nCountKeyPressed(0)
{}

HelloWorld::~HelloWorld() {}

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
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

	this->pTankHero = Sprite::create("res/sprites/tank_01_top.png");
	this->pTankHero->setPosition(Vec2(size.width / 2, size.height / 2));

	auto animation = Animation::create();
	for (int i = 1; i <= 8; i++) {
		std::string name = StringUtils::format("res/sprites/tank_%02d_top.png", i);
		animation->addSpriteFrameWithFile(name.c_str());
	}
	animation->setDelayPerUnit(0.15f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1);
	auto animate = Animate::create(animation);

	this->pAnimateMoveTrucks = (RepeatForever *)this->pTankHero->runAction(animate);

	this->addChild(this->pTankHero);

	this->pTankHero->getActionManager()->pauseTarget(this->pTankHero);

	this->scheduleUpdate();

    return true;
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	//log("Key with keycode %d released", keyCode);
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || 
		keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || 
		keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		nCountKeyPressed++;
		this->pTankHero->getActionManager()->resumeTarget(this->pTankHero);
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
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	//log("Key with keycode %d released", keyCode);

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		nCountKeyPressed--;
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
	if (nCountKeyPressed == 0) {
		/*dt = pAnimateMoveTrucks->getElapsed();
		pTankHero->getActionManager()->pauseAllRunningActions();*/
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
	else {

	}
}
