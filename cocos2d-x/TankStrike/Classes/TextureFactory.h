#pragma once

#include "cocos2d.h"

#include "defens.h"

using namespace cocos2d;

typedef std::tuple<uint8_t, uint8_t> tiletype;

class TextureFactory {
public:
	static const uint8_t maxXTile = 22;
	static const uint8_t maxYTile = 12;

	static TextureFactory &getInstance();

	SpriteFrame *getSprite(ObjType objType);
	Animate *getAnimate(ObjType objType);

	SpriteFrame *getPlayerTankSprite();
	Animate *getPlayerTankAnimate();

	SpriteFrame *getEnemyTankSprite();
	Animate *getEnemyTankAnimate();

	float getTileWidth() const;
	float getTileHeight() const;
private:
	TextureFactory();
	TextureFactory(const TextureFactory&) {}
	TextureFactory& operator=(const TextureFactory&) {}
private:
	const char *tiles_res = "res/sprites/tiles.png";
	static const uint16_t playerTankTile = 14;
	static const uint16_t playerTankAnimateTile = 14;
	static const uint16_t enemyTankTile = 17 + 4 * 22;
	static const uint16_t enemyTankAnimateTile = 15 + 9 * 22;
	static const uint16_t wallTile = 2 + 3 * 22;
	static const uint16_t groundTile = /*5*/3 + 3 * 22;
	static const uint16_t brickTile = 4 + 1 * 22;
	static const uint16_t eagleTile = 0 + 2 * 22;
	static const uint16_t shotTile = 7 + 0 * 22;
	static const uint16_t shotAnimateTile = 0;

	Texture2D *pTextures;

	SpriteFrame *pPlayerTank;
	SpriteFrame *pEnemyTank;
	SpriteFrame *pWall;
	SpriteFrame *pGround;
	SpriteFrame *pBrick;
	SpriteFrame *pEagle;
	SpriteFrame *pShot;

	Animate *pPlayerTankAnimate;
	Animate *pEnemyTankAnimate;
	Animate *pShotAnimate;

	float tileWidth;
	float tileHeight;
};
