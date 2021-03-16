#include <thread>

#include "EnemyTank.h"
#include "Shot.h"
#include "TextureFactory.h"
#include "BattleLayer.h"

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
		enemyTank->initPhysics();
		enemyTank->getPhysicsBody()->setContactTestBitmask(ObjType::ENEMY);
		return enemyTank;
	}

	CC_SAFE_DELETE(enemyTank);
	return NULL;
}

void EnemyTank::startGameLoop() {
	//std::thread gameLoop(&EnemyTank::calculateMove, this, 0, 0);
	//gameLoop.detach();
}

void EnemyTank::initTank(Maze *pMaze)
{
	Tank::initTank();
	//pMoveAnimate = TextureFactory::getInstance().getEnemyTankAnimate();
	pMoveAnimate = TextureFactory::getInstance().getAnimate(ObjType::ENEMY);
	pMoveAnimate->retain();
	nX_delta = 0;
	nY_delta = 0;
	direction = eDirection::UP;
    this->pMaze = pMaze;
	this->moveTo(eDirection::RIGHT);
	this->playAnimation();
}

std::tuple<uint16_t, uint16_t> EnemyTank::convertPos2Area(Vec2 pos) {
	Size sceneSize = Director::getInstance()->getWinSize();
	uint16_t x = pos.x / TextureFactory::getInstance().getTileWidth();
	uint16_t y = pos.y / TextureFactory::getInstance().getTileHeight();

	return std::tuple<uint16_t, uint16_t>(x, y);
}

std::tuple<uint16_t, uint16_t> EnemyTank::inaccurPos2Area(Vec2 pos) {
    Size sceneSize = Director::getInstance()->getWinSize();

    uint16_t x = pos.x / TextureFactory::getInstance().getTileWidth();
    uint16_t y = pos.y / TextureFactory::getInstance().getTileHeight();

    return std::tuple<uint16_t, uint16_t>(x * TextureFactory::getInstance().getTileWidth(),
                                          y *  TextureFactory::getInstance().getTileHeight());
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

void EnemyTank::update(float dt) {
	Tank::update(dt);
	//this->calculateMove();
}

void EnemyTank::setObjective(IObjective *pObjctv) {
	//Patrol patrol(10, 10);
}

void EnemyTank::calculateMove() {
	const char *eDirectionStr[] = {"LEFT", "RIGHT", "UP", "DOWN"};
    //std::this_thread::sleep_for(std::chrono::seconds{ 3 });
    
    pathfinder::TMap pathMap = pMaze->getPath();
    //do {
        Vec2 curPos = this->getPosition();
        std::tuple<uint16_t, uint16_t> curpos = EnemyTank::convertPos2Area(curPos);
        std::tuple<uint16_t, uint16_t> inaccurpos= EnemyTank::inaccurPos2Area(curPos);
        uint32_t curPosX = std::get<0>(curpos);
        uint32_t curPosY = MAZE_HEIGHT - std::get<1>(curpos);
        uint32_t inaccurPosX = std::get<0>(curpos);
        uint32_t inaccurPosY = MAZE_HEIGHT - std::get<1>(curpos);
        //cocos2d::log("corpos %.2f:.2%f => curPos %u:%u(%u:%u)\n", curPos.x, curPos.y, curPosX, curPosY, inaccurPosX, inaccurPosY);

        unsigned char c[4], c_min = 0xFF;

        c[0] = pathMap.getCell(curPosX - 1, curPosY);
        c[1] = pathMap.getCell(curPosX + 1, curPosY);
        c[2] = pathMap.getCell(curPosX, curPosY - 1);
        c[3] = pathMap.getCell(curPosX, curPosY + 1);

        //bool not_found = true;
        for (int i = 0; i < 4; i++) {
            if (c[i] <= c_min && c[i] != 0) {
                this->moveTo((eDirection)i);
                c_min = c[i];
                //not_found = false;
            }
        }
        //if (not_found) break;
        //std::this_thread::sleep_for(std::chrono::milliseconds{ 500 });
    //} while(true);
}
