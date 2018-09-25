#include "HeroTank.h"

HeroTank::~HeroTank()
{
	CC_SAFE_RELEASE(moveAnimate);
}

HeroTank *HeroTank::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
	HeroTank *heroTank = new HeroTank();
	if (heroTank && heroTank->initWithSpriteFrame(spriteFrame))
	{
		heroTank->autorelease();
		heroTank->initPlayer();
		return heroTank;
	}

	CC_SAFE_DELETE(heroTank);
	return NULL;
}

void HeroTank::initPlayer()
{
	moving = false;
	char str[100] = { 0 };
	
	Vector<SpriteFrame*> moveAnimFrames(6);
	for (int i = 1; i <= 4; i++)
	{
		sprintf(str, "move_%i.png", i);
		auto frame = SpriteFrame::create(str, Rect(0, 0, 68, 160));
		moveAnimFrames.pushBack(frame);
	}

	auto moveAnimation = Animation::createWithSpriteFrames(moveAnimFrames, 0.09f);
	moveAnimate = Animate::create(moveAnimation);
	moveAnimate->retain();
}

void HeroTank::move(int directionParam)
{
	this->stopAllActions();
	this->runAction(RepeatForever::create(moveAnimate));

	direction = directionParam;
	moving = true;
}

void HeroTank::idle()
{
	moving = false;
	this->stopAllActions();
	//this->runAction(RepeatForever::create(idleAnimate));
}

void HeroTank::update()
{
	if (moving) //check if moving
	{
		if (direction == 0) //check if going left
		{
			this->setScaleX(-1); //flip
			this->setPositionX(this->getPositionX() - 5);
		}
		else
		{
			this->setScaleX(1); //flip
			this->setPositionX(this->getPositionX() + 5);
		}
	}
}