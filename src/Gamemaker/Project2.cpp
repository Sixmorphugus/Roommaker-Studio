// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Project2.h"
#include "Platform.h"
#include "Folder.h"
#include "Object.h"
#include "Sprite.h"
#include "Room.h"

// rapidjson
#include "rapidjson/document.h"

// wx
#include <wx/progdlg.h>

using namespace std;

GMProject2::GMProject2(string ProjectPath, wxProgressDialog* ProgDlg)
	: GMResourceContainer(this)
{
	m_ProjectPath = ProjectPath;
	m_Valid = false;

	RMS_LogInfo("READING GameMaker Studio 2 Project: \"" + ProjectPath + "\"");

	// Ok we need to read the entire JSON file
	string JsonData;

	bool Succ = RMSPlatform::LoadTextFile(JsonData, ProjectPath);

	if (Succ)
	{
		try {
			// Try to read the doc
			rapidjson::Document Doc;
			Doc.Parse(JsonData.c_str());

			// make sure "resources" exists and is the right type
			assert(Doc.HasMember("resources"));
			assert(Doc["resources"].IsArray());

			auto ResourceList = Doc["resources"].GetArray();

			if(ProgDlg) ProgDlg->SetRange(ResourceList.Size() * 2 + 1);

			// Load individual resources.
			for (unsigned i = 0; i < ResourceList.Size(); i++)
			{
				if (ProgDlg) ProgDlg->Update(i, "Loading Resources...");

				auto& Resource = ResourceList[i];

				assert(Resource.IsObject());
				assert(Resource["Key"].IsString());

				assert(Resource["Value"].IsObject());
				assert(Resource["Value"]["resourcePath"].IsString());
				assert(Resource["Value"]["resourceType"].IsString());

				// Get Key
				string Key = Resource["Key"].GetString();

				// Get Path
				string Path = Resource["Value"]["resourcePath"].GetString();

				// Get Type
				string TypeStr = Resource["Value"]["resourceType"].GetString();
				GMResourceType Type = GMResourceType::Ignored;

				// Decide what the resource is.
				if (TypeStr == "GMSprite")
					Type = Sprite;
				else if (TypeStr == "GMRoom")
					Type = Room;
				else if (TypeStr == "GMObject")
					Type = Object;
				else if (TypeStr == "GMFolder")
					Type = Folder;
				else if (TypeStr == "GMTileSet")
					Type = TileSet;

				// Create a new resource and put it into the full resource list.
				// Note how we aren't doing anything with the ResourcesTopLevel list yet.
				// We'll generate that later.
				LoadResource(Key, Path, Type);
			}

			for (unsigned i = 0; i < m_Resources.size(); i++)
			{
				if (ProgDlg) ProgDlg->Update(ResourceList.Size() + i, "Initializing Resources...");

				auto& Resource = m_Resources[i];
				Resource->Init();
			}

			// Find the group "Default". That's the one that contains all the main filters.
			if (ProgDlg) ProgDlg->Update(ResourceList.Size() * 2 + 1, "Building Asset Tree...");

			for (auto& Resource : m_Resources)
			{
				GMFolder* Folder = dynamic_cast<GMFolder*>(Resource.get());

				if (Folder)
				{
					if  (Folder->IsDefaultFolder())
					{
						for (unsigned i = 0; i < Folder->GetNumResources(); i++)
						{
							GMResource* ResourceResource = Folder->GetResource(i);

							// sorry about this
							/*
							if (   ResourceResource->GetName() != "scripts"
								&& ResourceResource->GetName() != "sounds"
								&& ResourceResource->GetName() != "paths"
								&& ResourceResource->GetName() != "shaders"
								&& ResourceResource->GetName() != "fonts"
								&& ResourceResource->GetName() != "timelines"
								&& ResourceResource->GetName() != "notes"
								&& ResourceResource->GetName() != "datafiles"
								&& ResourceResource->GetName() != "extensions"
								&& ResourceResource->GetName() != "options"
								&& ResourceResource->GetName() != "configs"
							)
							*/
								m_ResourcesTopLevel.push_back(ResourceResource);
						}
					}
				}
			}

			if (ProgDlg) ProgDlg->Update(ResourceList.Size() * 2 + 1, "Done");

			RMSPlatform::Log("\tBuilt resource tree.");
			m_Valid = true;
		}
		catch (exception &e)
		{
			RMS_LogWarn("Exception thrown while reading \"" + ProjectPath + "\": \"" + e.what() + "\"");
		}
	}
	else
	{
		RMS_LogWarn("Failed to open file: \"" + ProjectPath + "\"");
	}
}

string GMProject2::GetProjectRoot()
{
	return RMSPlatform::Dir(m_ProjectPath);
}

GMResource* GMProject2::FindResource(std::string m_Key)
{
	for (auto& Resource : m_Resources)
	{
		if (Resource->GetKey() == m_Key)
			return Resource.get();
	}

	return nullptr;
}

unsigned GMProject2::GetNumResources()
{
	return m_ResourcesTopLevel.size();
}

GMResource* GMProject2::GetResource(unsigned i)
{
	if (i >= GetNumResources())
		return NULL;
	
	return m_ResourcesTopLevel[i];
}

void GMProject2::Save()
{
	// Does nothing YET
}

void GMProject2::LoadResource(string Key, string RelativePath, GMResourceType Type)
{
	// Debug message
	string ResTypeStr = "unknown";
	switch (Type)
	{
	case Object:
		ResTypeStr = "an Object";
		break;
	case Room:
		ResTypeStr = "a Room";
		break;
	case Sprite:
		ResTypeStr = "a Sprite";
		break;
	case TileSet:
		ResTypeStr = "a TileSet";
		break;
	case Folder:
		ResTypeStr = "a Folder";
		break;
	}

	RMSPlatform::Log("\tLoading " + Key + ", " + ResTypeStr);

	// Put a shared_ptr to the resource into the m_Resources list.
	shared_ptr<GMResource> NewResource;

	switch (Type)
	{
	case Object:
		NewResource = std::make_shared<GMObject>(this, Key, RelativePath);
		break;
	case Room:
		NewResource = std::make_shared<GMRoom>(this, Key, RelativePath);
		break;
	case Sprite:
		NewResource = std::make_shared<GMSprite>(this, Key, RelativePath);
		break;
	case TileSet:
		NewResource = std::make_shared<GMResource>(this, Key, RelativePath);
		break;
	case Folder:
		NewResource = std::make_shared<GMFolder>(this, Key, RelativePath);
		break;
	case Ignored:
		NewResource = std::make_shared<GMResource>(this, Key, RelativePath);
		break;
	}

	NewResource->SetSaveType(Type);

	m_Resources.push_back(NewResource);
}
