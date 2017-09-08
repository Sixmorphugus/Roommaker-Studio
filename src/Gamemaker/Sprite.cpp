// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Sprite.h"

#include "rapidjson/document.h"

using namespace std;

GMSprite::GMSprite(GMProject2* Project, string Key, string DataPath)
	: GMResource(Project, Key, DataPath)
{

	m_SpriteSetup.setTexture(m_Frame0);

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

			// Find our name
			assert(Doc["name"].IsString());
			SetName(Doc["name"].GetString());

			// Find Frame0
			assert(Doc["frames"].IsArray());
			auto JSA = Doc["frames"].GetArray();

			assert(JSA.Size() > 0);
			assert(JSA[0].IsObject());

			std::string Loc = RMSPlatform::Dir(GetRealPath()) + "/" + JSA[0]["id"].GetString();

			m_Frame0.loadFromFile(Loc);

			// Find the origin
			assert(Doc["xorig"].IsNumber());
			assert(Doc["yorig"].IsNumber());

			m_SpriteSetup.setOrigin(Doc["xorig"].GetInt(), Doc["yorig"].GetInt());
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
