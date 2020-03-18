#include <thread>
#include <random>

#include "EnemyTank.h"
#include "Shot.h"
#include "TextureFactory.h"
#include "BattleLayer.h"

int getRandom(int a, int b) {
    std::random_device random_device; // Источник энтропии.
    std::mt19937 generator(random_device()); // Генератор случайных чисел.
    std::uniform_int_distribution<> distribution(a, b); // Равномерное распределение [10, 20]

    return distribution(generator); // Случайное число.
}

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
	nX_delta = 0;
	nY_delta = 0;
	direction = eDirection::UP;
    this->pMaze = pMaze;
}

std::tuple<uint16_t, uint16_t> EnemyTank::convertPos2Area(Vec2 pos) {
	uint16_t x = static_cast<uint16_t>(pos.x / TextureFactory::getInstance().getTileWidth());
	uint16_t y = static_cast<uint16_t>(pos.y / TextureFactory::getInstance().getTileHeight());

	return std::tuple<uint16_t, uint16_t>(x, y);
}

bool EnemyTank::accurancyPosition(Vec2 pos) {
    float x = pos.x / TextureFactory::getInstance().getTileWidth();
    float y = pos.y / TextureFactory::getInstance().getTileHeight();

    return x == y == 0.0f;
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

void EnemyTank::setObjective(IObjective *pObjctv) {
	//Patrol patrol(10, 10);
}

void EnemyTank::calcParams() {
    Vec2 curPos = this->getPosition();
    if (accurancyPosition(curPos)) {
        //TODO считается что танк находится точно в центре клетки и может повернуть, вычисляем куда ему поворачивать
        const char *eDirectionStr[] = {"LEFT", "RIGHT", "UP", "DOWN"};
        std::tuple<uint16_t, uint16_t> curposеtuple = EnemyTank::convertPos2Area(curPos);
        uint32_t curPosX = std::get<0>(curposеtuple);
        uint32_t curPosY = MAZE_HEIGHT - std::get<1>(curposеtuple);

    }
}

void EnemyTank::calculateMove() {
	const char *eDirectionStr[] = {"LEFT", "RIGHT", "UP", "DOWN"};
    //std::this_thread::sleep_for(std::chrono::seconds{ 3 });

    //do {
        Vec2 curPos = this->getPosition();
        std::tuple<uint16_t, uint16_t> curpos = EnemyTank::convertPos2Area(curPos);
        uint32_t curPosX = std::get<0>(curpos);
        uint32_t curPosY = MAZE_HEIGHT - std::get<1>(curpos);
        uint32_t inaccurPosX = std::get<0>(curpos);
        uint32_t inaccurPosY = MAZE_HEIGHT - std::get<1>(curpos);
        //cocos2d::log("corpos %.2f:.2%f => curPos %u:%u(%u:%u)\n", curPos.x, curPos.y, curPosX, curPosY, inaccurPosX, inaccurPosY);

        unsigned char c[4], c_min = 0xFF;

        //if (not_found) break;
        //std::this_thread::sleep_for(std::chrono::milliseconds{ 500 });
    //} while(true);
}
