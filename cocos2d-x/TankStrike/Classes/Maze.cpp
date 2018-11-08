#include "Maze.h"
#include "EnemyTank.h"

/*
�� ������ � ��������� ���� ������:.
����� ����� ��������� �� ��������� ���� � ���������� �� ����� (������). ���� ��������, �� �������� �������� ���:
1) ���� ��������� ������ � �������� ��������� ���(� ��������� �������������� ���������� � % ���������� � ������� ����� �� 0 �� 100 � ���� ��� ������ % ����������, �� ������ ��� ������)
2) ������ ��������� �������� ������������� (���� ������ ������, ���� ��� ������ ���� � �������� < N ������ �� ������ � ������. ���� ��� �� �����, �� � �������� < M ������, �� ������ ������). � ����� ��������� ������ � ������ ���������. ��������� ��� ��������� X � ���. (N, M � X � �� �� ����������, � �������� ����� �������� � �� ��� ����� ������ �������� ���������)
3) ������ ��� ���� ������: ���� � ��������� ��������(������� � ��������� ������) � ������� �����, ������ � ��������� �������� ��� ����. ����� ������� � ��� ���� N � ������, ������� �� ������ ����� ������ ��������� ����� ����� ��� ������ ��������.

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

		pMaze->build();
		return pMaze;
	}

	CC_SAFE_DELETE(pMaze);
	return NULL;
}

void Maze::build() {
	for (uint16_t x = 0; x <= width; x++) {
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
