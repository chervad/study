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
	, pPlayerTank(nullptr)
	, pEnemyTank(nullptr)
	, pPlayerTankAnimate(nullptr)
{
	Rect rect = Rect::ZERO;
	rect.size = pTextures->getContentSize();
	tileWidth = rect.size.width / 22;
	tileHeight = rect.size.height / 12;

	pPlayerTank = SpriteFrame::createWithTexture(this->pTextures, TILERECT(playerTankTile, tileWidth, tileHeight));
	pPlayerTank->retain();

	pEnemyTank = SpriteFrame::createWithTexture(this->pTextures, TILERECT(enemyTankTile, tileWidth, tileHeight));
	pEnemyTank->retain();

	auto tankHeroAnimation = Animation::create();
	for (int i = 0; i < 8; i++) {
		Rect rect = Rect((14 + i) * this->tileWidth, 0 * this->tileHeight, this->tileWidth, this->tileHeight);
		SpriteFrame *frame = SpriteFrame::createWithTexture(this->pTextures, rect);
		tankHeroAnimation->addSpriteFrame(frame);
	}
	tankHeroAnimation->setDelayPerUnit(0.1f);
	tankHeroAnimation->setRestoreOriginalFrame(true);
	tankHeroAnimation->setLoops(-1);
	pPlayerTankAnimate = Animate::create(tankHeroAnimation);
	pPlayerTankAnimate->retain();
}

SpriteFrame *TextureFactory::getPlayerTankSprite() {
	return pPlayerTank;
}

SpriteFrame *TextureFactory::getEnemyTankSprite() {
	return pEnemyTank;
}

Animate *TextureFactory::getPlayerTankAnimate() {
	return pPlayerTankAnimate;
}
