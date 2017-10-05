// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

// and here
// we
// go

#include "GM.h"

#include <memory>

class GMSprite;
class GMAutoTile;

class RMSDLL GMTileSet : public GMResource
{
private:
	GMSprite* m_TextureSprite;

	bool m_SpriteNoExport;

	unsigned m_TileAnimationSpeed;
	unsigned m_TileCount;

	unsigned m_TileWidth;
	unsigned m_TileHeight;

	unsigned m_TileHSep;
	unsigned m_TileVSep;

	unsigned m_TileXOff;
	unsigned m_TileYOff;

	//std::vector<std::shared_ptr<GMAutoTile>> m_AutoTileSets;

public:
	GMTileSet(GMProject2* Project, std::string Key, std::string DataPath);

	virtual void Init();

	GMSprite* GetTextureSprite() const { return m_TextureSprite; }
	void SetTextureSprite(GMSprite* val) { m_TextureSprite = val; }

	bool GetSpriteNoExport() const { return m_SpriteNoExport; }
	void SetSpriteNoExport(bool val) { m_SpriteNoExport = val; }

	unsigned GetTileAnimationSpeed() const { return m_TileAnimationSpeed; }
	void SetTileAnimationSpeed(unsigned val) { m_TileAnimationSpeed = val; }

	unsigned GetTileCount() const { return m_TileCount; }
	void SetTileCount(unsigned val) { m_TileCount = val; }

	unsigned GetTileWidth() const { return m_TileWidth; }
	void SetTileWidth(unsigned val) { m_TileWidth = val; }
	unsigned GetTileHeight() const { return m_TileHeight; }
	void SetTileHeight(unsigned val) { m_TileHeight = val; }
	void SetTileSize(unsigned x, unsigned y) { m_TileWidth = x; m_TileHeight = y; }

	unsigned GetTileHSep() const { return m_TileHSep; }
	void SetTileHSep(unsigned val) { m_TileHSep = val; }
	unsigned GetTileVSep() const { return m_TileVSep; }
	void SetTileVSep(unsigned val) { m_TileVSep = val; }
	void SetTileSet(unsigned x, unsigned y) { m_TileHSep = x; m_TileVSep = y; }

	unsigned GetTileXOff() const { return m_TileXOff; }
	void SetTileXOff(unsigned val) { m_TileXOff = val; }
	unsigned GetTileYOff() const { return m_TileYOff; }
	void SetTileYOff(unsigned val) { m_TileYOff = val; }
	void SetTileOff(unsigned x, unsigned y) { m_TileXOff = x; m_TileYOff = y; }
};
