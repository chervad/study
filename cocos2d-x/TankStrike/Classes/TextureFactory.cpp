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
	, pWall(nullptr)
	, pGround(nullptr)
	, pBrick(nullptr)
	, pEagle(nullptr)
	, pShot(nullptr)

	, pPlayerTankAnimate(nullptr)
	, pEnemyTankAnimate(nullptr)
{
	Rect rect = Rect::ZERO;
	rect.size = pTextures->getContentSize();
	tileWidth = rect.size.width / 22;
	tileHeight = rect.size.height / 12;
	log("Tile size: %.2f x %.2f", tileWidth, tileHeight);

	auto pt = diff2tiletype(playerTankTile);
	auto pat = diff2tiletype(playerTankAnimateTile);
	pPlayerTank = SpriteFrame::createWithTexture(this->pTextures, TILERECT(pt, TextureFactory::tileWidth, TextureFactory::tileHeight));
	pPlayerTank->retain();

	auto et = diff2tiletype(enemyTankTile);
	auto eat = diff2tiletype(enemyTankAnimateTile);
	pEnemyTank = SpriteFrame::createWithTexture(this->pTextures, TILERECT(et, TextureFactory::tileWidth, TextureFactory::tileHeight));
	pEnemyTank->retain();

	auto wt = diff2tiletype(wallTile);
	pWall = SpriteFrame::createWithTexture(this->pTextures, TILERECT(wt, TextureFactory::tileWidth, TextureFactory::tileHeight));
	pWall->retain();

	auto gt = diff2tiletype(groundTile);
	pGround = SpriteFrame::createWithTexture(this->pTextures, TILERECT(gt, TextureFactory::tileWidth, TextureFactory::tileHeight));
	pGround->retain();

	auto bt = diff2tiletype(brickTile);
	pBrick = SpriteFrame::createWithTexture(this->pTextures, TILERECT(bt, TextureFactory::tileWidth, TextureFactory::tileHeight));
	pBrick->retain();

	pEagle = SpriteFrame::createWithTexture(this->pTextures, TILERECT(diff2tiletype(eagleTile), TextureFactory::tileWidth, TextureFactory::tileHeight));
	pEagle->retain();

	pShot = SpriteFrame::createWithTexture(this->pTextures, TILERECT(diff2tiletype(shotTile), TextureFactory::tileWidth, TextureFactory::tileHeight));
	pShot->retain();

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
	} else if (objType == ObjType::WALL) {
		return pWall;
	} else if (objType == ObjType::GROUND) {
		return pGround;
	} else if (objType == ObjType::BRICK) {
		return pBrick;
	} else if (objType == ObjType::EAGLE) {
		return pEagle;
	} else if (objType == ObjType::SHOT) {
		return pShot;
	}
	return nullptr;
}

Animate *TextureFactory::getAnimate(ObjType objType) {
	if (objType == ObjType::ENEMY) {
		return pEnemyTankAnimate;
	}
	else if (objType == ObjType::PLAYER) {
		return pPlayerTankAnimate;
	}
	return nullptr;
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
