#include "TextureFactory.h"

#define TX(X) std::get<0>(X)
#define TY(Y) std::get<1>(Y)
#define TILERECT(TILENAME, TILEWIDTH, TILEHEIGHT) Rect(TX(TILENAME) * TILEWIDTH, TY(TILENAME) * TILEHEIGHT, TILEWIDTH, TILEHEIGHT)

TextureFactory &TextureFactory::getInstance() {
	static TextureFactory instance;
	return instance;
}

TextureFactory::TextureFactory() 
	: pTextures(Director::getInstance()->getTextureCache()->addImage(tiles_res))
	, pHeroTank(nullptr)
	, pEnemyTank(nullptr)
{
	Rect rect = Rect::ZERO;
	rect.size = pTextures->getContentSize();
	tileWidth = rect.size.width / 22;
	tileHeight = rect.size.height / 12;

	pHeroTank = SpriteFrame::createWithTexture(this->pTextures, TILERECT(heroTankTile, tileWidth, tileHeight));
	pEnemyTank = SpriteFrame::createWithTexture(this->pTextures, TILERECT(enemyTankTile, tileWidth, tileHeight));
}

SpriteFrame *TextureFactory::getHeroTankSprite() {
	return pHeroTank;
}

SpriteFrame *TextureFactory::getEnemyTankSprite() {
	return pEnemyTank;
}
