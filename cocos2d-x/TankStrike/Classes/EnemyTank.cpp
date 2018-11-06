#include "EnemyTank.h"

#include "TextureFactory.h"

EnemyTank::~EnemyTank()
{
	CC_SAFE_RELEASE(pMoveAnimate);
}

EnemyTank *EnemyTank::create()
{
	EnemyTank *tank = new EnemyTank();
	if (tank && tank->initWithSpriteFrame(TextureFactory::getInstance().getEnemyTankSprite()))
	{
		tank->autorelease();
		tank->initTank();
		return tank;
	}

	CC_SAFE_DELETE(tank);
	return NULL;
}

void EnemyTank::initTank()
{
	pMoveAnimate = TextureFactory::getInstance().getEnemyTankAnimate();
	nX_delta = 0;
	nY_delta = 0;
	//eDirection = MoveDirection::UP;
}

/*void PlayerTank::runMoveAnimate() {
if (!pCurrentMoveAction) {
stopAction(pCurrentMoveAction);
}
pCurrentMoveAction = runAction(RepeatForever::create(pMoveAnimate));
}*/

/*void PlayerTank::stopMoveAnimate() {
if (!pCurrentMoveAction) {
stopAction(pCurrentMoveAction);
}
}*/

std::tuple<uint16_t, uint16_t> EnemyTank::convertPos2Area(Vec2 pos) {
	Size sceneSize = Director::getInstance()->getWinSize();
	uint16_t x = pos.x / TextureFactory::getInstance().getTileWidth();
	uint16_t y = pos.y / TextureFactory::getInstance().getTileHeight();

	return { x, y };
}

Vec2 EnemyTank::convertArea2Pos(uint16_t areaX, uint16_t areaY) {
	Size sceneSize = Director::getInstance()->getWinSize();
	float x = areaX * TextureFactory::getInstance().getTileWidth() + (TextureFactory::getInstance().getTileWidth() / 2);
	float y = areaY * TextureFactory::getInstance().getTileHeight() + (TextureFactory::getInstance().getTileHeight() / 2);
	return Vec2(x, y);
}

Vec2 EnemyTank::convertArea2Pos(std::tuple<uint16_t, uint16_t> area) {
	return convertArea2Pos(std::get<0>(area), std::get<1>(area));
}

void EnemyTank::moveToArea(MoveDirection direct, int deltaArea) {
	
}
