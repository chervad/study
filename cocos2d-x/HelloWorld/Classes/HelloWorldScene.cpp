#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    if (!Layer::init())
    {

        return false;
    }
	Size size = Director::getInstance()->getWinSize();
	auto sprite = Sprite::create("res/sprites/tanks_all.png");
	sprite->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(sprite);
    return true;
}
