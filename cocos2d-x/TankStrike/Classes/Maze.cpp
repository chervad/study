#include <array>
#include "Maze.h"
#include "EnemyTank.h"

#define AUTOGENERATE false

const char mazePlan[19][26] = {
	  "xxxxxxxxxxxxxxxxxxxxxxxxx"
	, "x                       x"
	, "xx  xxxx  xxxx  xxxx  xxx"
	, "x                       x"
	, "xxxxx  xxxx  xxxx  xxxxxx"
	, "x                       x"
	, "xx  xxxx  xxxx  xxxx  xxx"
	, "x                       x"
	, "xxxxx  xxxx  xxxx  xxxxxx"
	, "x                       x"
	, "xx  xxxx  xxxx  xxxx  xxx"
	, "x                       x"
	, "xxxxx  xxxx  xxxx  xxxxxx"
	, "x                       x"
	, "xx  xxxx  xxxx  xxxx  xxx"
	, "x                       x"
	, "x   x     xxx     x     x"
	, "x   x     xEx     x     x"
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
	for (auto wall : listWall) {
		CC_SAFE_DELETE(wall);
	}
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

bool Maze::moveTankThisPosition(Vec2 vpos, Tank::MoveDirection direct) {
	std::tuple<uint16_t, uint16_t> pos = EnemyTank::convertPos2Area(vpos);
	uint16_t x = std::get<0>(pos);
	uint16_t y = std::get<1>(pos);
	log("Current to position: %.2f x %.2f -> %d x %d. Block: %c", vpos.x, vpos.y, x, y);
	switch (direct) {
	case Tank::MoveDirection::LEFT:
		x += -1;
		break;
	case Tank::MoveDirection::RIGHT:
		x += 1;
		break;
	case  Tank::MoveDirection::UP:
		y += 1;
		break;
	case  Tank::MoveDirection::DOWN:
		y += -1;
		break;
	}
	if (x >= 0 && x <= 26 && y >= 0 && y < 19) {
		char block = mazePlan[19 - y - 1][x];
		log("Move to position: %d x %d. Block: %c", x, y, block);
		return block == ' ' ? true : false;
	}
	return false;
}

void Maze::build() {
	if (isAutogenerate) {
		for (uint16_t x = 0; x < width; x++) {
			Wall *pWall = GameObject::create<Wall>();
			pWall->setPosition(EnemyTank::convertArea2Pos(x, 0));
			this->listWall.push_back(pWall);
			this->pParentNode->addChild(pWall);

			pWall = GameObject::create<Wall>();
			pWall->setPosition(EnemyTank::convertArea2Pos(x, height));
			this->listWall.push_back(pWall);
			this->pParentNode->addChild(pWall);
		}

		for (uint16_t y = 1; y < height; y++) {
			Wall *pWall = GameObject::create<Wall>();
			pWall->setPosition(EnemyTank::convertArea2Pos(0, y));
			this->listWall.push_back(pWall);
			this->pParentNode->addChild(pWall);

			pWall = GameObject::create<Wall>();
			pWall->setPosition(EnemyTank::convertArea2Pos(width, y));
			this->listWall.push_back(pWall);
			this->pParentNode->addChild(pWall);
		}
	}
	else {
		for (uint16_t x = 0; x < width; x++) {
			for (uint16_t y = 0; y < height; y++) {
				char block = mazePlan[height - y - 1][x];
				if (block == 'x') {
					Wall *pWall = GameObject::create<Wall>();
					pWall->setPosition(EnemyTank::convertArea2Pos(x, y));
					this->listWall.push_back(pWall);
					this->pParentNode->addChild(pWall);
				}
			}
		}
	}
}
