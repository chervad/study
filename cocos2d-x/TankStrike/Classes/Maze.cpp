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
По картам с комнатами была статья:.
Также видел алгоритмы по генерации карт в туториалах по Юнити (ссылка). Если примерно, то алгоритм выглядит так:
1) Берём двумерный массив и рандомом заполняем его(в туториале использовалась переменная — % заполнения — генерим число от 0 до 100 и 
если оно меньше % заполнения, то ставим тут стенку)
2) Делаем несколько итераций «сглаживания» (берём каждую клетку, если это стенка если её окружает < N стенок то делаем её пустой. 
Если это не стена, но её окружает < M стенок, то делаем стенку). В итоге «одинокие» стенки и «дырки» пропадают. 
Повторяем эту процедуру X — раз. (N, M и X — то же переменные, с которыми можно играться и от них будет сильно зависить результат)
3) Делаем два лист листов: один — коллекция областей(область — коллекция клеток) в которых стены, второй — коллекция областей без стен.
Таким образом у нас есть N — комнат, которые мы теперь можем просто соединить между собой или просто сдвинуть.

Играясь с переменными будет получаться совершенно разный результат. Тут ещё стоит учитывать что «сглаживание» увеличивает разрыв между пустыми клетками и клетками со стенами. В моём случае в 45-48% заполнения получались большие пустые области с несколькими комнатками, а в случае 52-55% — много небольших-средних комнатушек.
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
