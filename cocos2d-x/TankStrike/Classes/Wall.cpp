#include "Wall.h"

#include "TextureFactory.h"

Wall::~Wall() {

}

Wall *Wall::create() {
	Wall *wall = new Wall();
	if (wall && wall->initWithSpriteFrame(TextureFactory::getInstance().getEnemyTankSprite()))
	{
		wall->autorelease();
		return wall;
	}

	CC_SAFE_DELETE(wall);
	return NULL;
}

void Wall::initObject() {
}
