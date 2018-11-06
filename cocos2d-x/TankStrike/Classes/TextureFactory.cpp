#include "TextureFactory.h"

#define TX(X) std::get<0>(X)
#define TY(Y) std::get<1>(Y)
#define TILERECT(TILEDIFF, TILEWIDTH, TILEHEIGHT) Rect(TX(TILEDIFF) * TILEWIDTH, TY(TILEDIFF) * TILEHEIGHT, TILEWIDTH, TILEHEIGHT)

inline tiletype diff2tiletype(uint16_t d) {
	uint8_t x = d % TextureFactory::maxXTile;
	uint8_t y = d / TextureFactory::maxXTile;
	return {x, y};
}

TextureFactory &TextureFactory::getInstance() {
	static TextureFactory instance;
	return instance;
}

TextureFactory::TextureFactory() 
	: pTextures(Director::getInstance()->getTextureCache()->addImage(tiles_res))
	, pPlayerTank(nullptr)
	, pEnemyTank(nullptr)
	, pPlayerTankAnimate(nullptr)
	, pEnemyTankAnimate(nullptr)
{
	Rect rect = Rect::ZERO;
	rect.size = pTextures->getContentSize();
	tileWidth = rect.size.width / 22;
	tileHeight = rect.size.height / 12;

	auto pt = diff2tiletype(playerTankTile);
	auto pat = diff2tiletype(playerTankAnimateTile);
	pPlayerTank = SpriteFrame::createWithTexture(this->pTextures, TILERECT(pt, TextureFactory::tileWidth, TextureFactory::tileHeight));
	pPlayerTank->retain();

	auto et = diff2tiletype(enemyTankTile);
	auto eat = diff2tiletype(enemyTankAnimateTile);
	pEnemyTank = SpriteFrame::createWithTexture(this->pTextures, TILERECT(et, TextureFactory::tileWidth, TextureFactory::tileHeight));
	pEnemyTank->retain();

	auto playerTankAnimation = Animation::create();
	for (int i = 0; i < 8; i++) {
		Rect rect = Rect((TX(pat) + i) * this->tileWidth, TY(pat) * this->tileHeight, this->tileWidth, this->tileHeight);
		SpriteFrame *frame = SpriteFrame::createWithTexture(this->pTextures, rect);
		playerTankAnimation->addSpriteFrame(frame);
	}
	playerTankAnimation->setDelayPerUnit(0.1f);
	playerTankAnimation->setRestoreOriginalFrame(true);
	playerTankAnimation->setLoops(-1);
	pPlayerTankAnimate = Animate::create(playerTankAnimation);
	pPlayerTankAnimate->retain();

	auto enemyTankAnimation = Animation::create();
	for (int i = 0; i < 8; i++) {
		Rect rect = Rect((TX(eat) + i) * this->tileWidth, TY(eat) * this->tileHeight, this->tileWidth, this->tileHeight);
		SpriteFrame *frame = SpriteFrame::createWithTexture(this->pTextures, rect);
		enemyTankAnimation->addSpriteFrame(frame);
	}
	enemyTankAnimation->setDelayPerUnit(0.1f);
	enemyTankAnimation->setRestoreOriginalFrame(true);
	enemyTankAnimation->setLoops(-1);
	pEnemyTankAnimate = Animate::create(enemyTankAnimation);
	pEnemyTankAnimate->retain();
}

SpriteFrame *TextureFactory::getSprite(ObjType objType) {
	if (objType == ObjType::ENEMY) {
		return pEnemyTank;
	} else if (objType == ObjType::PLAYER) {
		return pPlayerTank;
	}
}

Animate *TextureFactory::getAnimate(ObjType objType) {
	if (objType == ObjType::ENEMY) {
		return pEnemyTankAnimate;
	}
	else if (objType == ObjType::PLAYER) {
		return pPlayerTankAnimate;
	}
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

Animate *TextureFactory::getEnemyTankAnimate() {
	return pEnemyTankAnimate;
}

float TextureFactory::getTileWidth() const {
	return tileWidth;
}

float TextureFactory::getTileHeight() const {
	return tileHeight;
}
