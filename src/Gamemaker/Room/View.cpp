// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Room/View.h"
#include "GM.h"
#include "Object.h"
#include "Room.h"
#include "Project2.h"

void GMRView::SetDefaults()
{
	m_Id = GenerateGUID();

	m_HBorder = 32;
	m_VBorder = 32;

	m_HSpeed = -1;
	m_VSpeed = -1;

	m_XPort = 0;
	m_YPort = 0;
	m_WPort = 800;
	m_HPort = 600;

	m_XView = 0;
	m_YView = 0;
	m_WView = 800;
	m_HView = 600;

	m_Visible = false;

	m_Inherit = false;

	m_Object = NULL;
}

GMRView::GMRView(GMRoom* Room)
{
	m_Room = Room;
	SetDefaults();
}

GMRView::GMRView(GMRoom* Room, rapidjson::GenericObject<false, rapidjson::GenericValue<rapidjson::UTF8<>>>& StoredView)
{
	m_Room = Room;
	SetDefaults();

	// not entirely sure how GMS's GUID system works or where it allows duplicates so we don't care if this fails
	assert(StoredView["id"].IsString());
	RegisterTakenGUID(StoredView["id"].GetString());

	assert(StoredView["hborder"].IsNumber());
	m_HBorder = StoredView["hborder"].GetInt();
	assert(StoredView["vborder"].IsNumber());
	m_VBorder = StoredView["vborder"].GetInt();

	assert(StoredView["hspeed"].IsNumber());
	m_HSpeed = StoredView["hspeed"].GetInt();
	assert(StoredView["vspeed"].IsNumber());
	m_VSpeed = StoredView["vspeed"].GetInt();

	assert(StoredView["xport"].IsNumber());
	m_XPort = StoredView["xport"].GetInt();
	assert(StoredView["yport"].IsNumber());
	m_YPort = StoredView["yport"].GetInt();
	assert(StoredView["wport"].IsNumber());
	m_WPort = StoredView["wport"].GetInt();
	assert(StoredView["hport"].IsNumber());
	m_HPort = StoredView["hport"].GetInt();

	assert(StoredView["xview"].IsNumber());
	m_XView = StoredView["xview"].GetInt();
	assert(StoredView["yview"].IsNumber());
	m_YView = StoredView["yview"].GetInt();
	assert(StoredView["wview"].IsNumber());
	m_WView = StoredView["wview"].GetInt();
	assert(StoredView["hview"].IsNumber());
	m_HView = StoredView["hview"].GetInt();

	assert(StoredView["visible"].IsBool());
	m_Visible = StoredView["visible"].GetBool();

	assert(StoredView["inherit"].IsBool());
	m_Inherit = StoredView["inherit"].GetBool();

	// Find follow object
	assert(StoredView["objId"].IsString());
	auto Resource = m_Room->GetProject()->FindResource(StoredView["objId"].GetString());
	m_Room = dynamic_cast<GMRoom*>(Resource);
}

rapidjson::Document GMRView::GetJSON()
{
	rapidjson::Document StoredView;

	StoredView["id"].SetString(m_Id.c_str(), m_Id.size());
	StoredView["modelName"] = "GMRView";

	if (m_Object)
	{
		StoredView["objId"].SetString(m_Object->GetKey().c_str(), m_Object->GetKey().size());
	}
	else
	{
		auto guid = GenerateGUID(true);
		StoredView["objId"].SetString(guid.c_str(), guid.size());
	}

	StoredView["hborder"] = m_HBorder;
	StoredView["vborder"] = m_VBorder;

	StoredView["hspeed"] = m_HSpeed;
	StoredView["vspeed"] = m_VSpeed;

	StoredView["xport"] = m_XPort;
	StoredView["yport"] = m_YPort;
	StoredView["wport"] = m_WPort;
	StoredView["hport"] = m_HPort;

	StoredView["visible"] = m_Visible;

	StoredView["inherit"] = m_Inherit;

	return StoredView;
}
