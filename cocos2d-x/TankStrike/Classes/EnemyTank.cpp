#include <thread>

#include "EnemyTank.h"

#include "TextureFactory.h"

//#include "Objectives/Patrol.h"

EnemyTank::~EnemyTank()
{
	CC_SAFE_RELEASE(pMoveAnimate);
}

EnemyTank *EnemyTank::create(Maze *pMaze)
{
	EnemyTank *enemyTank = new EnemyTank();
	if (enemyTank && enemyTank->initWithSpriteFrame(TextureFactory::getInstance().getEnemyTankSprite()))
	{
		//enemyTank->autorelease();
		enemyTank->initTank(pMaze);
		//enemyTank->initPhysics();
		//enemyTank->getPhysicsBody()->setContactTestBitmask(ObjType::ENEMY);
		return enemyTank;
	}

	CC_SAFE_DELETE(enemyTank);
	return NULL;
}

void EnemyTank::startGameLoop() {
	std::thread gameLoop(&EnemyTank::calculateMove, this, 0, 0);
	gameLoop.detach();
}

void EnemyTank::initTank(Maze *pMaze)
{
	Tank::initTank();
	//pMoveAnimate = TextureFactory::getInstance().getEnemyTankAnimate();
	pMoveAnimate = TextureFactory::getInstance().getAnimate(ObjType::ENEMY);
	nX_delta = 0;
	nY_delta = 0;
	direction = eDirection::UP;
    this->pMaze = pMaze;
}

std::tuple<uint16_t, uint16_t> EnemyTank::convertPos2Area(Vec2 pos) {
	Size sceneSize = Director::getInstance()->getWinSize();
	uint16_t x = pos.x / TextureFactory::getInstance().getTileWidth();
	uint16_t y = pos.y / TextureFactory::getInstance().getTileHeight();

	return std::tuple<uint16_t, uint16_t>(x, y);
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

/*void EnemyTank::update(float dt) {
	Tank::update(dt);
}*/

void EnemyTank::setObjective(IObjective *pObjctv) {
	//Patrol patrol(10, 10);
}

void EnemyTank::calculateMove(int posX, int posY) {
    pathfinder::TMap map = pMaze->getPath();
    std::tuple<uint16_t, uint16_t> curpos = EnemyTank::convertPos2Area(this->getPosition());
    uint32_t curPosX = std::get<0>(curpos);
    uint32_t curPosY = std::get<1>(curpos);
    char c[4], c_min = 0xFF;
    c[0] = map.getCell(curPosX - 1, curPosY);
    c[1] = map.getCell(curPosX + 1, curPosY);
    c[2] = map.getCell(curPosX, curPosY - 1);
    c[3] = map.getCell(curPosX, curPosY + 1);

    eDirection dir[4] = {eDirection::LEFT, eDirection::RIGHT, eDirection::DOWN, eDirection::UP};
    for (int i = 0; i < 4; i++) {
        if (c[i] < c_min) {
            this->moveTo(dir[i]);
        }
    }
}
