// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Room/Layer.h"
#include "Room.h"

void GMRLayer::SetDefaults(GMRoom* Room)
{
	m_Name = "Layer";
	m_Id = GenerateGUID();

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

GMRLayer::GMRLayer(GMRoom* Room, rapidjson::Value& StoredLayer)
{
	SetDefaults(Room);

	assert(StoredLayer["id"].IsString());
	m_Id = StoredLayer["id"].GetString();

	RegisterTakenGUID(m_Id);

	assert(StoredLayer["name"].IsString());
	m_Name = StoredLayer["name"].GetString();

	assert(StoredLayer["depth"].IsInt());
	m_Depth = StoredLayer["depth"].GetInt();

	assert(StoredLayer["grid_x"].IsInt());
	m_GridX = StoredLayer["grid_x"].GetInt();
	assert(StoredLayer["grid_y"].IsInt());
	m_GridY = StoredLayer["grid_y"].GetInt();

	assert(StoredLayer["hierarchyFrozen"].IsBool());
	m_HierarchyFrozen = StoredLayer["hierarchyFrozen"].GetBool();
	assert(StoredLayer["hierarchyVisible"].IsBool());
	m_HierarchyVisible = StoredLayer["hierarchyVisible"].GetBool();

	assert(StoredLayer["inheritLayerDepth"].IsBool());
	m_InheritLayerDepth = StoredLayer["inheritLayerDepth"].GetBool();
	assert(StoredLayer["inheritLayerSettings"].IsBool());
	m_InheritLayerSettings = StoredLayer["inheritLayerSettings"].GetBool();
	assert(StoredLayer["inheritSubLayers"].IsBool());
	m_InheritSubLayers = StoredLayer["inheritSubLayers"].GetBool();
	assert(StoredLayer["inheritVisibility"].IsBool());
	m_InheritVisibility = StoredLayer["inheritVisibility"].GetBool();

	assert(StoredLayer["m_serialiseFrozen"].IsBool());
	m_SerialiseFrozen = StoredLayer["m_serialiseFrozen"].GetBool();

	assert(StoredLayer["userdefined_depth"].IsBool());
	m_UserdefinedDepth = StoredLayer["userdefined_depth"].GetBool();

	assert(StoredLayer["visible"].IsBool());
	m_Visible = StoredLayer["visible"].GetBool();

	// Find the parent layer
	assert(StoredLayer["m_parentID"].IsString());
	std::string SearchId = StoredLayer["m_parentID"].GetString();

	for (unsigned i = 0; i < Room->GetNumLayers(); i++)
	{
		auto Layer = Room->GetLayer(i);

		if (Layer->GetKey() == SearchId)
		{
			m_Parent = Layer;
		}
	}
}

GMRLayer::GMRLayer(GMRoom* Room)
{
	SetDefaults(Room);
}

void GMRLayer::Draw(sf::RenderTarget& Target) const
{}

void GMRLayer::DrawActive(sf::RenderTarget& Target)
{
	sf::VertexArray lines(sf::Lines);

	int GridSizeX = m_Room->GetWidth() / m_GridX;
	int GridSizeY = m_Room->GetHeight() / m_GridY;

	for (int x = 0; x < GridSizeX + 1; x++)
	{
		// draw x vertical lines from the top to the bottom of the room
		sf::Vertex v1;
		v1.position.x = x * m_GridX;
		v1.position.y = 0;
		v1.color = sf::Color(150, 150, 150, 150);

		sf::Vertex v2;
		v2.position.x = x * m_GridX;
		v2.position.y = m_Room->GetHeight();
		v2.color = sf::Color(150, 150, 150, 150);

		lines.append(v1);
		lines.append(v2);
	}

	for (int y = 0; y < GridSizeY + 1; y++)
	{
		// draw y horizontal lines from the left to the right of the room
		sf::Vertex v1;
		v1.position.x = 0;
		v1.position.y = y * m_GridY;
		v1.color = sf::Color(150, 150, 150, 150);

		sf::Vertex v2;
		v2.position.x = m_Room->GetWidth();
		v2.position.y = y * m_GridY;
		v2.color = sf::Color(150, 150, 150, 150);

		lines.append(v1);
		lines.append(v2);
	}

	Target.draw(lines);
}

rapidjson::Document GMRLayer::GetJSON() const
{
	rapidjson::Document StoredLayer;

	StoredLayer["mvc"] = "1.0";

	StoredLayer["id"].SetString(m_Id.c_str(), m_Id.size());
	StoredLayer["name"].SetString(m_Name.c_str(), m_Id.size());
	StoredLayer["depth"] = m_Depth;

	StoredLayer["grid_x"] = m_GridX;
	StoredLayer["grid_y"] = m_GridY;

	StoredLayer["hierarchyFrozen"] = m_HierarchyFrozen;
	StoredLayer["hierarchyVisible"] = m_HierarchyVisible;

	StoredLayer["inheritLayerDepth"] = m_InheritLayerDepth;
	StoredLayer["inheritLayerSettings"] = m_InheritLayerDepth;
	StoredLayer["inheritSubLayers"] = m_InheritSubLayers;
	StoredLayer["inheritVisibility"] = m_InheritVisibility;

	StoredLayer["m_serialiseFrozen"] = m_SerialiseFrozen;

	StoredLayer["userdefined_depth"] = m_UserdefinedDepth;

	StoredLayer["visible"] = m_Visible;

	if (m_Parent)
	{
		StoredLayer["m_parentID"].SetString(m_Parent->GetKey().c_str(), m_Parent->GetKey().size());
	}
	else
	{
		auto guid = GenerateGUID(true);
		StoredLayer["m_parentID"].SetString(guid.c_str(), guid.size());
	}

	return StoredLayer;
}
