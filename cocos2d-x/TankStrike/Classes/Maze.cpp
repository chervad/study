#include "Maze.h"
#include "EnemyTank.h"
#include "Ground.h"
#include "Brick.h"
#include "Wall.h"
#include "Eagle.h"
#include "BattleLayer.h"

#define AUTOGENERATE false

static char mazePlan[MAZE_HEIGHT + 1][MAZE_WIDTH] = {
	  "xxxxxxxxxxxxxxxxxxxxxxxxx"
	, "xT                     Tx"
	, "xx  xxxx  xxxx  xxxx  xxx"
	, "xT                     Tx"
	, "xbbbb  bbbb  bbbb  bbbbbx"
	, "xT                     Tx"
	, "xx  xxxx  xxxx  xxxx  xxx"
	, "xT                     Tx"
	, "xbbbb  bbbb  bbbb  bbbbbx"
	, "x                       x"
	, "xx  xxxx  xxxx  xxxx  xxx"
	, "x                       x"
	, "xbbbb  bbbb  bbbb  bbbbbx"
	, "x                       x"
	, "xx  bbbb  xxxx  bbbb  xxx"
	, "x                       x"
	, "x   x     bbb     x     x"
	, "x   x     bEb     x     x"
	, "xxxxxxxxxxxxxxxxxxxxxxxxx"
};

/*
�� ������ � ��������� ���� ������:.
����� ����� ��������� �� ��������� ���� � ���������� �� ����� (������). ���� ��������, �� �������� �������� ���:
1) ���� ��������� ������ � �������� ��������� ���(� ��������� �������������� ���������� � % ���������� � ������� ����� �� 0 �� 100 � 
���� ��� ������ % ����������, �� ������ ��� ������)
2) ������ ��������� �������� ������������� (���� ������ ������, ���� ��� ������ ���� � �������� < N ������ �� ������ � ������. 
���� ��� �� �����, �� � �������� < M ������, �� ������ ������). � ����� ��������� ������ � ������ ���������. 
��������� ��� ��������� X � ���. (N, M � X � �� �� ����������, � �������� ����� �������� � �� ��� ����� ������ �������� ���������)
3) ������ ��� ���� ������: ���� � ��������� ��������(������� � ��������� ������) � ������� �����, ������ � ��������� �������� ��� ����.
����� ������� � ��� ���� N � ������, ������� �� ������ ����� ������ ��������� ����� ����� ��� ������ ��������.

������� � ����������� ����� ���������� ���������� ������ ���������. ��� ��� ����� ��������� ��� ������������ ����������� ������ ����� ������� �������� � �������� �� �������. � ��� ������ � 45-48% ���������� ���������� ������� ������ ������� � ����������� ����������, � � ������ 52-55% � ����� ���������-������� ����������.
*/

Maze::~Maze() {
	/*for (auto wall : listWall) {
		CC_SAFE_DELETE(wall);
	}*/
}

Maze *Maze::create(uint16_t width, uint16_t height, Node *pParentNode) {
	Maze *pMaze = new Maze();
	if (pMaze)
	{
		pMaze->width = width;
		pMaze->height = height;
		pMaze->pParentNode = pParentNode;
		pMaze->isAutogenerate = AUTOGENERATE;

		log("Creating maze: %d x %d", pMaze->width, pMaze->height);

		pMaze->build();
		return pMaze;
	}

	CC_SAFE_DELETE(pMaze);
	return NULL;
}

void Maze::build() {
	if (isAutogenerate) {
		for (uint16_t x = 0; x < width; x++) {
			Wall *pWall = GameObject::create<Wall>();
			pWall->setPosition(EnemyTank::convertArea2Pos(x, 0));
			//this->listWall.push_back(pWall);
			this->pParentNode->addChild(pWall);

			pWall = GameObject::create<Wall>();
			pWall->setPosition(EnemyTank::convertArea2Pos(x, height));
			//this->listWall.push_back(pWall);
			this->pParentNode->addChild(pWall);
		}

		for (uint16_t y = 1; y < height; y++) {
			Wall *pWall = GameObject::create<Wall>();
			pWall->setPosition(EnemyTank::convertArea2Pos(0, y));
			//this->listWall.push_back(pWall);
			this->pParentNode->addChild(pWall);

			pWall = GameObject::create<Wall>();
			pWall->setPosition(EnemyTank::convertArea2Pos(width, y));
			//this->listWall.push_back(pWall);
			this->pParentNode->addChild(pWall);
		}
	}
	else {
		for (uint16_t x = 0; x < width; x++) {
			for (uint16_t y = 0; y < height; y++) {
				char block = mazePlan[height - y - 1][x];
				Ground *pGround = GameObject::create<Ground>();
				pGround->setPosition(EnemyTank::convertArea2Pos(x, y));
				this->pParentNode->addChild(pGround);

				if (block == 'x') {
					Wall *pWall = GameObject::create<Wall>();
					pWall->setPosition(EnemyTank::convertArea2Pos(x, y));
					//this->listWall.push_back(pWall);
					this->pParentNode->addChild(pWall);
				} else if (block == 'b') {
					Brick *pBrick = GameObject::create<Brick>();
					pBrick->setPosition(EnemyTank::convertArea2Pos(x, y));
					this->pParentNode->addChild(pBrick);
				} else if (block == 'E') {
					Eagle *pEagle = GameObject::create<Eagle>();
					pEagle->setPosition(EnemyTank::convertArea2Pos(x, y));
					this->pParentNode->addChild(pEagle);
				} else if (block == 'T') {
					BattleLayer *pBattleLayer = (BattleLayer *)this->pParentNode;
					pBattleLayer->addEnemyBase(EnemyTank::convertArea2Pos(x, y));
				}
			}
		}
	}
}
//TODO �������������, � ������ ������������� � ������������� �����, �������� �����������
pathfinder::TMap Maze::getPath() {
    PlayerTank *pPTank = ((BattleLayer *)pParentNode)->getPlayerTank();
    Vec2 player_position = pPTank->getPosition();
    std::tuple<uint16_t, uint16_t> pl_pos = EnemyTank::convertPos2Area(player_position);
    uint16_t destPosX = std::get<0>(pl_pos);
    uint16_t destPosY = std::get<1>(pl_pos);
    const char *pplan[19];
    for (int i = 0; i < 19; ++i) {
        pplan[i] = mazePlan[i];
    }
    pathfinder::TMap map = pathfinder::TMap::create(pplan, 26, 19);//TODO ����� �� ��� ����� ����������, ������� ����� ���� � �������� � ������� �����������
    pathfinder::TPoint p(destPosX, destPosY);
    //map.print();
    pathfinder::TMap result = map.findAllPath(p);
    return result;
}

bool Maze::moveTankThisPosition(Vec2 newPos, float width, float height, eDirection direction) {
	Vec2 checkPos_leftTrack = newPos;
	Vec2 checkPos_rightTrack = newPos;

	switch (direction) {
	case eDirection::LEFT:
		checkPos_leftTrack.x += -1 * width;
		checkPos_leftTrack.y += -1 * height;

		checkPos_rightTrack.x += -1 * width;
		checkPos_rightTrack.y += height;
		break;
	case eDirection::RIGHT:
		checkPos_leftTrack.x += width;
		checkPos_leftTrack.y += height;

		checkPos_rightTrack.x += width;
		checkPos_rightTrack.y += -1 * height;
		break;
	case eDirection::UP:
		checkPos_leftTrack.x += -1 * width;
		checkPos_leftTrack.y += height;

		checkPos_rightTrack.x += width;
		checkPos_rightTrack.y += height;
		break;
	case eDirection::DOWN:
		checkPos_leftTrack.x += width;
		checkPos_leftTrack.y += -1 * height;

		checkPos_rightTrack.x += -1 * width;
		checkPos_rightTrack.y += -1 * height;
		break;
	}

	std::tuple<uint16_t, uint16_t> pos_1 = EnemyTank::convertPos2Area(checkPos_leftTrack);
	std::tuple<uint16_t, uint16_t> pos_2 = EnemyTank::convertPos2Area(checkPos_rightTrack);

	uint16_t x1 = std::get<0>(pos_1);
	uint16_t y1 = std::get<1>(pos_1);

	uint16_t x2 = std::get<0>(pos_2);
	uint16_t y2 = std::get<1>(pos_2);
    //TODO T - ��������� ����, ����� ����� �� ���� ��������?
	return mazePlan[19 - y1 - 1][x1] == ' ' || mazePlan[19 - y1 - 1][x1] == 'T'
		&& mazePlan[19 - y2 - 1][x2] == ' ' || mazePlan[19 - y2 - 1][x2] == 'T';
}

void Maze::setMazePlan(Vec2 pos, char block) {
   	std::tuple<uint16_t, uint16_t> post = EnemyTank::convertPos2Area(pos);
	uint16_t x = std::get<0>(post);
	uint16_t y = std::get<1>(post);
	y = 19 - y - 1;
	char old = mazePlan[y][x];
	mazePlan[y][x] = block;
}

char Maze::getMazePlan(Vec2 pos) {
    std::tuple<uint16_t, uint16_t> post = EnemyTank::convertPos2Area(pos);
    uint16_t x = std::get<0>(post);
    uint16_t y = std::get<1>(post);
    y = 19 - y - 1;
    return mazePlan[y][x];
}
