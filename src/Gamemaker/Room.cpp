// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Room.h"

#include "Room/Layer/BackgroundLayer.h"
#include "Room/Layer/InstanceLayer.h"
#include "Room/Layer/AssetLayer.h"
#include "Room/Layer/TileMapLayer.h"

#include "rapidjson/document.h"

using namespace std;

void GMRoom::SetDefaults()
{
	// Room stuff
	m_CreationCode = "";
	m_ParentRoom = NULL;

	// Physics Settings
	m_isPhysicsWorld = false;
	m_PhysicsWorldGravityX = 0.f;
	m_PhysicsWorldGravityY = 10.f;
	m_PhysicsWorldPixToMeters = 0.1f;
	m_PhysicsWorldInheritSettings = false;

	// Room Settings
	m_Width = 800;
	m_Height = 600;
	m_Persistent = false;
	m_InheritSettings = false;

	// View Settings
	m_EnableViews = false;
	m_ViewsClearDisplayBuffer = true;
	m_ViewsClearBackground = false;
	m_ViewsInheritSettings = false;

	m_ActiveLayer = NULL;

	for (unsigned i = 0; i < 8; i++)
	{
		m_Views[i] = make_shared<GMRView>(this);
	}
}

GMRoom::GMRoom(GMProject2* Project, string Key, string DataPath)
	: GMResource(Project, Key, DataPath)
{
	SetDefaults();

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

			// Read physics world settings
			{
				assert(Doc["physicsSettings"].IsObject());
				auto physSettings = Doc["physicsSettings"].GetObject();

				assert(physSettings["PhysicsWorld"].IsBool());
				m_isPhysicsWorld = physSettings["PhysicsWorld"].GetBool();

				assert(physSettings["PhysicsWorldGravityX"].IsNumber());
				m_PhysicsWorldGravityX = physSettings["PhysicsWorldGravityX"].GetFloat();

				assert(physSettings["PhysicsWorldGravityY"].IsNumber());
				m_PhysicsWorldGravityY = physSettings["PhysicsWorldGravityY"].GetFloat();

				assert(physSettings["PhysicsWorldPixToMeters"].IsNumber());
				m_PhysicsWorldPixToMeters = physSettings["PhysicsWorldPixToMeters"].GetFloat();

				assert(physSettings["inheritPhysicsSettings"].IsBool());
				m_PhysicsWorldInheritSettings = physSettings["inheritPhysicsSettings"].GetBool();
			}

			// Read room settings
			{
				assert(Doc["roomSettings"].IsObject());
				auto roomSettings = Doc["roomSettings"].GetObject();

				assert(roomSettings["Width"].IsInt());
				m_Width = roomSettings["Width"].GetInt();

				assert(roomSettings["Height"].IsInt());
				m_Height = roomSettings["Height"].GetInt();

				assert(roomSettings["persistent"].IsBool());
				m_Persistent = roomSettings["persistent"].GetBool();

				assert(roomSettings["inheritRoomSettings"].IsBool());
				m_InheritSettings = roomSettings["inheritRoomSettings"].GetBool();
			}

			// Read view settings
			{
				assert(Doc["viewSettings"].IsObject());
				auto viewSettings = Doc["viewSettings"].GetObject();

				assert(viewSettings["enableViews"].IsBool());
				m_EnableViews = viewSettings["enableViews"].GetBool();

				assert(viewSettings["clearDisplayBuffer"].IsBool());
				m_ViewsClearDisplayBuffer = viewSettings["clearDisplayBuffer"].GetBool();

				assert(viewSettings["clearViewBackground"].IsBool());
				m_ViewsClearBackground = viewSettings["clearViewBackground"].GetBool();

				assert(viewSettings["inheritViewSettings"].IsBool());
				m_ViewsInheritSettings = viewSettings["inheritViewSettings"].GetBool();
			}

			// Read views
			{
				assert(Doc["views"].IsArray());
				auto ViewsArray = Doc["views"].GetArray();

				for (unsigned i = 0; i < 8; i++)
				{
					assert(ViewsArray[i].IsObject());
					m_Views[i] = make_shared<GMRView>(this, ViewsArray[i]);
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

std::shared_ptr<GMRLayer> GMRoom::LayerFromJSON(GMRoom* Room, rapidjson::Value& Layer)
{
	assert(Layer["modelName"].IsString());
	string ModelName = Layer["modelName"].GetString();

	// Create generic layers
	if (ModelName == "GMRBackgroundLayer")
	{
		return make_shared<GMRBackgroundLayer>(Room, Layer);
	}
	else if (ModelName == "GMRInstanceLayer")
	{
		return make_shared<GMRInstanceLayer>(Room, Layer);
	}
	else if (ModelName == "GMRAssetLayer")
	{
		return make_shared<GMRAssetLayer>(Room, Layer);
	}
	else if (ModelName == "GMRTileLayer")
	{
		return make_shared<GMRTileMapLayer>(Room, Layer);
	}
	else if (ModelName == "GMRLayer")
	{
		return make_shared<GMRLayer>(Room, Layer);
	}
	else
	{
		RMS_LogWarn("\t\tUnknown layer type " + ModelName + ", defaulting to GMRLayer");
		return make_shared<GMRLayer>(Room, Layer);
	}
}

void GMRoom::Init()
{
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

			// Read layers
			{
				assert(Doc["layers"].IsArray());
				auto LayersArray = Doc["layers"].GetArray();

				for (unsigned i = 0; i < LayersArray.Size(); i++)
				{
					assert(LayersArray[i].IsObject());
					auto& Layer = LayersArray[i];

					m_Layers.push_back(LayerFromJSON(this, Layer));
				}

				if (m_Layers.size() > 0)
				{
					m_ActiveLayer = m_Layers[0].get();
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

	// layers are loaded backwards by default.
	reverse(m_Layers.begin(), m_Layers.end());
}

rapidjson::Document GMRoom::GetJSON() const
{
	rapidjson::Document Stored;

	// TODO

	return Stored;
}

GMRView* GMRoom::GetView(unsigned i) const
{
	if (i >= 8)
		return NULL;

	return m_Views[i].get();
}

GMRLayer* GMRoom::GetLayer(unsigned i) const
{
	if (i >= m_Layers.size())
		return NULL;

	return m_Layers[i].get();
}

void GMRoom::SetActiveLayer(GMRLayer* Layer)
{
	assert(Layer->GetRoom() == this);
	m_ActiveLayer = Layer;
}

GMRLayer* GMRoom::GetActiveLayer() const
{
	return m_ActiveLayer;
}
