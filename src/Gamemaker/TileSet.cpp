// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "TileSet.h"
#include "Project2.h"
#include "Sprite.h"

#include "rapidjson/document.h"

using namespace std;

GMTileSet::GMTileSet(GMProject2* Project, std::string Key, std::string DataPath)
	: GMResource(Project, Key, DataPath)
{
	string RealPath = GetRealPath();
	string JsonData;

	// Load object's JSON file.
	// It's complex but we don't care how the object works; Just what sprite it uses and what to call it.
	bool Succ = RMSPlatform::LoadTextFile(JsonData, RealPath);

	if (Succ)
	{
		try
		{
			// Try to read the doc
			rapidjson::Document Doc;
			Doc.Parse(JsonData.c_str());

			assert(Doc["name"].IsString());
			SetName(Doc["name"].GetString());

			assert(Doc["sprite_no_export"].IsBool());
			m_SpriteNoExport = Doc["sprite_no_export"].GetBool();

			assert(Doc["tile_animation_speed"].IsUint());
			m_TileAnimationSpeed = Doc["tile_animation_speed"].GetUint();

			assert(Doc["tile_count"].IsUint());
			m_TileCount = Doc["tile_count"].GetUint();

			assert(Doc["tilewidth"].IsUint());
			m_TileWidth = Doc["tilewidth"].GetUint();

			assert(Doc["tileheight"].IsUint());
			m_TileHeight = Doc["tileheight"].GetUint();

			assert(Doc["tilehsep"].IsInt());
			m_TileHSep = Doc["tilehsep"].GetInt();

			assert(Doc["tilevsep"].IsInt());
			m_TileVSep = Doc["tilevsep"].GetInt();

			assert(Doc["tilexoff"].IsInt());
			m_TileXOff = Doc["tilexoff"].GetInt();

			assert(Doc["tileyoff"].IsInt());
			m_TileYOff = Doc["tileyoff"].GetInt();
		}
		catch (std::exception &e)
		{
			RMS_LogWarn("Exception thrown while reading \"" + RealPath + "\": \"" + e.what() + "\"");
		}
	}
	else
	{
		RMS_LogWarn("Failed to open file: \"" + RealPath + "\"");
	}
}

void GMTileSet::Init()
{
	string RealPath = GetRealPath();
	string JsonData;

	// Load object's JSON file.
	// It's complex but we don't care how the object works; Just what sprite it uses and what to call it.
	bool Succ = RMSPlatform::LoadTextFile(JsonData, RealPath);

	if (Succ)
	{
		try
		{
			// Try to read the doc
			rapidjson::Document Doc;
			Doc.Parse(JsonData.c_str());

			// read sprite ID
			assert(Doc["spriteId"].IsString());
			string SpriteID = Doc["spriteId"].GetString();

			m_TextureSprite = dynamic_cast<GMSprite*>(GetProject()->FindResource(SpriteID));
		}
		catch (std::exception &e)
		{
			RMS_LogWarn("Exception thrown while reading \"" + RealPath + "\": \"" + e.what() + "\"");
		}
	}
	else
	{
		RMS_LogWarn("Failed to open file: \"" + RealPath + "\"");
	}
}

