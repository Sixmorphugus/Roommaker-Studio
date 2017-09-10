// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Room/View.h"

void GMView::SetDefaults()
{
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
}

GMView::GMView()
{
	SetDefaults();
}

GMView::GMView(rapidjson::GenericObject<false, rapidjson::GenericValue<rapidjson::UTF8<>>>& StoredView)
{
	SetDefaults();

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
}
