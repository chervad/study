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

bool Maze::moveTankThisPosition(Vec2 curPos, Vec2 newPos, Size size, Tank::MoveDirection eDirection) {
	size.width -= 6;
	size.height -= 6;

	float width = size.width / 2;
	float height = size.height / 2;

	Vec2 checkPos_leftTrack = newPos;
	Vec2 checkPos_rightTrack = newPos;

	switch (eDirection) {
	case Tank::MoveDirection::LEFT:
		checkPos_leftTrack.x += -1 * width;
		checkPos_leftTrack.y += -1 * height;

		checkPos_rightTrack.x += -1 * width;
		checkPos_rightTrack.y += height;
		break;
	case Tank::MoveDirection::RIGHT:
		checkPos_leftTrack.x += width;
		checkPos_leftTrack.y += height;

		checkPos_rightTrack.x += width;
		checkPos_rightTrack.y += -1 * height;
		break;
	case Tank::MoveDirection::UP:
		checkPos_leftTrack.x += -1 * width;
		checkPos_leftTrack.y += height;

		checkPos_rightTrack.x += width;
		checkPos_rightTrack.y += height;
		break;
	case Tank::MoveDirection::DOWN:
		checkPos_leftTrack.x += width;
		checkPos_leftTrack.y += -1 * height;

		checkPos_rightTrack.x += -1 * width;
		checkPos_rightTrack.y += -1 * height;
		break;
	}

	std::tuple<uint16_t, uint16_t> pos_1= EnemyTank::convertPos2Area(checkPos_leftTrack);
	std::tuple<uint16_t, uint16_t> pos_2 = EnemyTank::convertPos2Area(checkPos_rightTrack);

	uint16_t x1 = std::get<0>(pos_1);
	uint16_t y1 = std::get<1>(pos_1);

	uint16_t x2 = std::get<0>(pos_2);
	uint16_t y2 = std::get<1>(pos_2);

	return mazePlan[19 - y1 - 1][x1] == ' ' && mazePlan[19 - y2 - 1][x2] == ' ' ? true : false;
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
