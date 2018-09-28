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
	static const uint16_t enemyTankTile = (17 + 4 * 22);
	static const uint16_t enemyTankAnimateTile = (15 + 9 * 22);

	Texture2D *pTextures;

	SpriteFrame *pPlayerTank;
	SpriteFrame *pEnemyTank;

	Animate *pPlayerTankAnimate;
	Animate *pEnemyTankAnimate;

	float tileWidth;
	float tileHeight;
};
