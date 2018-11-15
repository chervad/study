#pragma once

#include "cocos2d.h"

#include "defens.h"

#include <array>

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
	//Animate *getPlayerTankAnimate();

	SpriteFrame *getEnemyTankSprite();
	//Animate *getEnemyTankAnimate();

	const std::array<SpriteFrame *, 4> &getBricks() const;

	float getTileWidth() const;
	float getTileHeight() const;
private:
	TextureFactory();
	TextureFactory(const TextureFactory&) {}
	TextureFactory& operator=(const TextureFactory&) {}
private:
	const char *tiles_res = "res/sprites/tiles.png";
	const uint16_t playerTankTile = 14;
	const uint16_t playerTankAnimateTile = 14;
	const uint16_t enemyTankTile = 17 + 4 * 22;
	const uint16_t enemyTankAnimateTile = 15 + 9 * 22;
	const uint16_t wallTile = 2 + 3 * 22;
	const uint16_t groundTile = 3 + 3 * 22;
	const uint16_t eagleTile = 0 + 2 * 22;
	const uint16_t shotTile = 7 + 0 * 22;
	const uint16_t shotAnimateTile = 0;

	const uint16_t brickTiles[4] = { 4 + 1 * 22, 0 + 7 * 22, 1 + 7 * 22, 2 + 7 * 22 };

	Texture2D *pTextures;

	SpriteFrame *pPlayerTank;
	SpriteFrame *pEnemyTank;
	SpriteFrame *pWall;
	SpriteFrame *pGround;
	std::array<SpriteFrame *, 4> pBricks;
	SpriteFrame *pEagle;
	SpriteFrame *pShot;

	Animate *pPlayerTankAnimate;
	Animate *pEnemyTankAnimate;
	Animate *pShotAnimate;

	float tileWidth;
	float tileHeight;
};
