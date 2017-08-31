// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Folder.h"
#include "Project2.h"

#include "rapidjson/document.h"

using namespace std;

GMFolder::GMFolder(GMProject2* Project, string Key, string DataPath)
	: GMResource(Project, Key, DataPath)
{
	vector<string> ChildIDs;
	string RealPath = GetRealPath();

	// Let's read our datafile:
	RMSPlatform::Log("\t\tReal path is " + RealPath);

	// Ok we need to read the entire JSON file
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
					for (auto& Resource : GetProject()->m_Resources)
					{
						if (Resource->GetKey() == Child.GetString())
						{
							Parent(Resource.get());
							m_Resources.push_back(Resource.get());
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

