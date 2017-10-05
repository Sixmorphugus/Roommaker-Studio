// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Room/Layer/TileMapLayer.h"

#include "TileSet.h"
#include "Room.h"
#include "Project2.h"

using namespace std;

GMRTileMapLayer::GMRTileMapLayer(GMRoom* Room, GMTileSet* TileSet)
	: GMRLayer(Room)
{
	m_TileSet = TileSet;

	SetPrevTileSize(m_TileSet->GetTileWidth(), m_TileSet->GetTileHeight());
	SetSerialiseSize(Room->GetWidth() / m_TileSet->GetTileWidth(), Room->GetWidth() / m_TileSet->GetTileHeight());
}

GMRTileMapLayer::GMRTileMapLayer(GMRoom* Room, rapidjson::Value& StoredLayer)
	: GMRLayer(Room, StoredLayer)
{
	// This is actually a little tricky.
	// We can't just set our defaults here because we don't have a tileset to set them with - hence the lack of a standard "SetDefaults" function
	//  on this class.

	// Luckily we don't really NEED any defaults here.

	// Load tileset asset from given key
	assert(StoredLayer["tilesetId"].IsString());
	string TKey = StoredLayer["tilesetId"].GetString();

	m_TileSet = dynamic_cast<GMTileSet*>(GetRoom()->GetProject()->FindResource(TKey));

	// Load tilemap's preview settings
	assert(StoredLayer["prev_tilewidth"].IsUint());
	SetPrevTileWidth(StoredLayer["prev_tilewidth"].GetUint());
	assert(StoredLayer["prev_tileheight"].IsUint());
	SetPrevTileHeight(StoredLayer["prev_tileheight"].GetUint());

	// Load tilemap information
	assert(StoredLayer["tiles"].IsObject());

	rapidjson::Value& TI = StoredLayer["tiles"];

	assert(TI["SerialiseWidth"].IsUint());
	assert(TI["SerialiseHeight"].IsUint());
	m_SerialiseWidth = TI["SerialiseWidth"].GetUint();
	m_SerialiseHeight = TI["SerialiseHeight"].GetUint();

	// Finally, load the tiles and decompress them from 32 bit binary
	// TODO
}

rapidjson::Document GMRTileMapLayer::GetJSON() const
{
	// Get base layer info
	rapidjson::Document StoredLayer = GMRLayer::GetJSON();

	// Change the model name
	StoredLayer["__type"] = "GMRTileLayer_Model:#YoYoStudio.MVCFormat";
	StoredLayer["modelName"] = "GMRTileLayer";

	// Store tileset key
	string TKey = m_TileSet->GetKey();
	StoredLayer["id"].SetString(TKey.c_str(), TKey.size());

	// Store preview information
	StoredLayer["prev_tilewidth"] = m_PrevTileWidth;
	StoredLayer["prev_tileheight"] = m_PrevTileHeight;

	// Store tilemap information
	StoredLayer["tiles"].SetObject();

	rapidjson::Value& TI = StoredLayer["tiles"];

	TI["SerialiseData"].SetNull();

	TI["SerialiseWidth"] = m_SerialiseWidth;
	TI["SerialiseHeight"] = m_SerialiseHeight;

	// Store the tiles, in their compressed 32 bit format
	// TODO

	return StoredLayer;
}

void GMRTileMapLayer::Draw(sf::RenderTarget& Target) const
{
	// ...

	GMRLayer::Draw(Target);
}

