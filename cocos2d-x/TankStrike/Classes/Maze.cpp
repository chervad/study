#include "Maze.h"
#include "EnemyTank.h"

/*
По картам с комнатами была статья:.
Также видел алгоритмы по генерации карт в туториалах по Юнити (ссылка). Если примерно, то алгоритм выглядит так:
1) Берём двумерный массив и рандомом заполняем его(в туториале использовалась переменная — % заполнения — генерим число от 0 до 100 и если оно меньше % заполнения, то ставим тут стенку)
2) Делаем несколько итераций «сглаживания» (берём каждую клетку, если это стенка если её окружает < N стенок то делаем её пустой. Если это не стена, но её окружает < M стенок, то делаем стенку). В итоге «одинокие» стенки и «дырки» пропадают. Повторяем эту процедуру X — раз. (N, M и X — то же переменные, с которыми можно играться и от них будет сильно зависить результат)
3) Делаем два лист листов: один — коллекция областей(область — коллекция клеток) в которых стены, второй — коллекция областей без стен. Таким образом у нас есть N — комнат, которые мы теперь можем просто соединить между собой или просто сдвинуть.

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
