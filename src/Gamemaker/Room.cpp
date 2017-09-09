// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Room.h"

#include "rapidjson/document.h"

using namespace std;

GMRoom::GMRoom(GMProject2* Project, string Key, string DataPath)
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