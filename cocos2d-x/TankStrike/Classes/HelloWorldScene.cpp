#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

//SING_NS_CC;
using namespace cocos2d;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
    return scene;
}

/*static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}*/

bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }
	Size size = Director::getInstance()->getWinSize();

	auto sprite = Sprite::create();// "res/sprites/tank_01_top.png");
	sprite->setPosition(Vec2(size.width / 2, size.height / 2));
	sprite->setScale(2.0f);
	sprite->setRotation(45.0f);

	auto animation = Animation::create();
	for (int i = 1; i <= 8; i++) {
		std::string name = StringUtils::format("res/sprites/tank_%02d_top.png", i);
		animation->addSpriteFrameWithFile(name.c_str());
	}
	animation->setDelayPerUnit(0.15f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1);
	auto action = Animate::create(animation);
	sprite->runAction(action);
	this->addChild(sprite);
    return true;
}
