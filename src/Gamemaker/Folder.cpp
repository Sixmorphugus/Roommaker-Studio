// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Folder.h"
#include "Project2.h"

#include "rapidjson/document.h"

using namespace std;

GMFolder::GMFolder(GMProject2* Project, string Key, string DataPath)
	: GMResource(Project, Key, DataPath), GMResourceContainer(Project)
{
	m_DefaultFolder = false;

	string RealPath = GetRealPath();

	// Let's read our datafile:
	string JsonData;

	bool Succ = RMSPlatform::LoadTextFile(JsonData, RealPath);

	if (Succ)
	{
		try
		{
			// Try to read the doc
			rapidjson::Document Doc;
			Doc.Parse(JsonData.c_str());

			// Find our name
			assert(Doc["folderName"].IsString());
			SetName(Doc["folderName"].GetString());

			// Find our filtertype
			assert(Doc["filterType"].IsString());

			string TypeStr = Doc["filterType"].GetString();
			m_FilterType = GMResourceType::Ignored;

			if (TypeStr == "GMSprite")
				m_FilterType = Sprite;
			else if (TypeStr == "GMRoom")
				m_FilterType = Room;
			else if (TypeStr == "GMObject")
				m_FilterType = Object;
			else if (TypeStr == "GMTileSet")
				m_FilterType = TileSet;

			// Find if we're a default view
			assert(Doc["isDefaultView"].IsBool());
			m_DefaultFolder = Doc["isDefaultView"].GetBool();
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

void GMFolder::Init()
{
	vector<string> ChildIDs;
	string RealPath = GetRealPath();

	// Let's read our datafile:
	RMSPlatform::Log("\tParenting folder children " + RealPath);
	string JsonData;

	bool Succ = RMSPlatform::LoadTextFile(JsonData, RealPath);

	if (Succ)
	{
		try
		{
			// Try to read the doc
			rapidjson::Document Doc;
			Doc.Parse(JsonData.c_str());

			// Find and verify the existance of the child list.
			assert(Doc["children"].IsArray());

			// Go through it.
			for (auto& Child : Doc["children"].GetArray())
			{
				assert(Child.IsString());

				// Find this child in the central resource list.
				for (auto& Child : Doc["children"].GetArray())
				{
					for (unsigned i = 0; i < GetNumAllResources(); i++)
					{
						auto Resource = GetAllResource(i);

						if (Resource->GetKey() == Child.GetString() && Resource->GetParent() != this)
						{
							Parent(Resource);
							m_Resources.push_back(Resource);
						}
					}
				}
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

GMResource* GMFolder::GetResource(unsigned i) const
{
	if (i >= GetNumResources())
		return NULL;

	return m_Resources[i];
}
