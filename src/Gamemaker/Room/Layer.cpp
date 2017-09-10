// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Room/Layer.h"
#include "Room.h"

void GMLayer::SetDefaults(GMRoom* Room)
{
	m_Name = "Layer";
	m_Id = "";

	m_Depth = 0;

	m_GridX = 32;
	m_GridY = 32;

	m_HierarchyFrozen = false;
	m_HierarchyVisible = true;

	m_InheritLayerDepth = false;
	m_InheritLayerSettings = false;
	m_InheritSubLayers = false;
	m_InheritVisibility = false;

	m_Room = Room;
	m_Parent = NULL;

	m_SerialiseFrozen = false;
	m_UserdefinedDepth = false;

	m_Visible = true;
}

GMLayer::GMLayer(GMRoom* Room, rapidjson::GenericObject<false, rapidjson::GenericValue<rapidjson::UTF8<>>>& StoredView)
{
	SetDefaults(Room);

	assert(StoredView["id"].IsString());
	m_Id = StoredView["id"].GetString();

	assert(StoredView["name"].IsString());
	m_Name = StoredView["name"].GetString();

	assert(StoredView["depth"].IsInt());
	m_Depth = StoredView["depth"].GetInt();

	assert(StoredView["grid_x"].IsInt());
	m_GridX = StoredView["grid_x"].GetInt();
	assert(StoredView["grid_y"].IsInt());
	m_GridY = StoredView["grid_y"].GetInt();

	assert(StoredView["hierarchyFrozen"].IsBool());
	m_HierarchyFrozen = StoredView["hierarchyFrozen"].GetBool();
	assert(StoredView["hierarchyVisible"].IsBool());
	m_HierarchyVisible = StoredView["hierarchyVisible"].GetBool();

	assert(StoredView["inheritLayerDepth"].IsBool());
	m_InheritLayerDepth = StoredView["inheritLayerDepth"].GetBool();
	assert(StoredView["inheritLayerSettings"].IsBool());
	m_InheritLayerDepth = StoredView["inheritLayerSettings"].GetBool();
	assert(StoredView["inheritSubLayers"].IsBool());
	m_InheritLayerDepth = StoredView["inheritSubLayers"].GetBool();
	assert(StoredView["inheritVisibility"].IsBool());
	m_InheritLayerDepth = StoredView["inheritVisibility"].GetBool();

	assert(StoredView["m_serialiseFrozen"].IsBool());
	m_SerialiseFrozen = StoredView["m_serialiseFrozen"].GetBool();

	assert(StoredView["userdefined_depth"].IsBool());
	m_SerialiseFrozen = StoredView["userdefined_depth"].GetBool();

	assert(StoredView["visible"].IsBool());
	m_Visible = StoredView["visible"].GetBool();

	// Find the parent layer
	assert(StoredView["m_parentID"].IsString());
	std::string SearchId = StoredView["m_parentID"].GetString();

	for (unsigned i = 0; i < Room->GetNumLayers(); i++)
	{
		auto Layer = Room->GetLayer(i);

		if (Layer->GetId() == SearchId)
		{
			m_Parent = Layer;
		}
	}
}

GMLayer::GMLayer(GMRoom* Room)
{
	SetDefaults(Room);
}
