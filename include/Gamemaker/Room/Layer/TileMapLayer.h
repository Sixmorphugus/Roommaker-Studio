// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once
#include "Room/Layer.h"

class GMTileSet;
class GMRUnpackedTile;

// ok let's not panic too much here guys
class GMRTileMapLayer : public GMRLayer
{
private:
	GMTileSet* m_TileSet;

	std::vector<std::shared_ptr<GMRUnpackedTile>> m_SerialiseDataUnpacked;

	unsigned m_SerialiseWidth;
	unsigned m_SerialiseHeight;

	unsigned m_PrevTileWidth;
	unsigned m_PrevTileHeight;

public:
	GMRTileMapLayer(GMRoom* Room, GMTileSet* TileSet); // default constructor
	GMRTileMapLayer(GMRoom* Room, rapidjson::Value& Stored); // loaded room constructor

	virtual rapidjson::Document GetJSON() const;
	virtual void Draw(sf::RenderTarget& Target) const;

	GMTileSet* GetTileSet() const { return m_TileSet; }
	void SetTileSet(GMTileSet* val) { m_TileSet = val; }

	unsigned GetSerialiseWidth() const { return m_SerialiseWidth; }
	void SetSerialiseWidth(unsigned val) { m_SerialiseWidth = val; }
	unsigned GetSerialiseHeight() const { return m_SerialiseHeight; }
	void SetSerialiseHeight(unsigned val) { m_SerialiseHeight = val; }
	void SetSerialiseSize(unsigned x, unsigned y) { SetSerialiseWidth(x); SetSerialiseHeight(y); }

	unsigned GetPrevTileWidth() const { return m_PrevTileWidth; }
	void SetPrevTileWidth(unsigned val) { m_PrevTileWidth = val; }
	unsigned GetPrevTileHeight() const { return m_PrevTileHeight; }
	void SetPrevTileHeight(unsigned val) { m_PrevTileHeight = val; }
	void SetPrevTileSize(unsigned x, unsigned y) { SetPrevTileWidth(x); SetPrevTileHeight(y); }
};