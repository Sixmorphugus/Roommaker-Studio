// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Object.h"
#include "Sprite.h"
#include "Project2.h"

#include "rapidjson/document.h"

using namespace std;

GMObject::GMObject(GMProject2* Project, string Key, string DataPath)
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

void GMObject::Init()
{
	// Which sprite's our sprite?
	// We can only know by reading the JSON again.

	string RealPath = GetRealPath();
	string JsonData;

	bool Succ = RMSPlatform::LoadTextFile(JsonData, RealPath);

	if (Succ)
	{
		try
		{
			// Try to read the doc
			rapidjson::Document Doc;
			Doc.Parse(JsonData.c_str());

			assert(Doc["spriteId"].IsString());
			m_Sprite = dynamic_cast<GMSprite*>(
				GetProject()->FindResource(
					Doc["spriteId"].GetString()
				)
			); // For certain reasons, this won't fail much - and even if it does it's not an issue.

			// TEMP
			if (m_Sprite)
			{
				SetName(GetName() + " #" + m_Sprite->GetName());
			}
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
