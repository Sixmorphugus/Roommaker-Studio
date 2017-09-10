// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "RoomProperties.h"
#include "Editor.h"
#include "Room.h"

using namespace std;

RMSRoomProperties::RMSRoomProperties(wxWindow *parent, wxWindowID id /*= wxID_ANY*/, const wxPoint& pos /*= wxDefaultPosition*/, const wxSize& size /*= wxDefaultSize*/, long style /*= wxPG_DEFAULT_STYLE*/, const wxString& name /*= "Room Properties"*/)
	: wxPropertyGrid(parent, id, pos, size, style, name)
{
	// Add all the required properties

	// ROOM SETTINGS
	m_NRoomCat = Append(new wxPropertyCategory("No room is loaded."));

	m_RoomCat = Append(new wxPropertyCategory("Room"));

	Append(new wxIntProperty("Width", wxPG_LABEL, 800));
	Append(new wxIntProperty("Height", wxPG_LABEL, 600));
	Append(new wxBoolProperty("Persistent?", wxPG_LABEL, false));
	Append(new wxBoolProperty("Inherit Parent setup?", wxPG_LABEL, false));

	m_RoomCat->Hide(true);

	// PHYSICS WORLD SETTINGS
	m_PhysCat = Append(new wxPropertyCategory("Physics World"));

	Append(new wxBoolProperty("Is Physics World?", wxPG_LABEL, false));
	Append(new wxFloatProperty("Physics World Gravity X", wxPG_LABEL, 0.f));
	Append(new wxFloatProperty("Physics World Gravity Y", wxPG_LABEL, 10.f));
	Append(new wxFloatProperty("Meters per Pixel", wxPG_LABEL, 0.1f));
	Append(new wxBoolProperty("Inherit Parent physics?", wxPG_LABEL, false));

	m_PhysCat->Hide(true);

	// VIEWS SETTINGS
	m_ViewsCat = Append(new wxPropertyCategory("Views"));

	Append(new wxBoolProperty("Enable Views?", wxPG_LABEL, false));
	Append(new wxBoolProperty("Views clear display buffer?", wxPG_LABEL, false));
	Append(new wxBoolProperty("Views clear background?", wxPG_LABEL, false));
	Append(new wxBoolProperty("Inherit Parent view settings?", wxPG_LABEL, false));

	for (unsigned i = 0; i < 8; i++)
	{
		auto viewEnabled = Append(new wxBoolProperty("View " + to_string(i), wxPG_LABEL, false));

		AppendIn(viewEnabled, new wxIntProperty("XPort", wxPG_LABEL, 0));
		AppendIn(viewEnabled, new wxIntProperty("YPort", wxPG_LABEL, 0));
		AppendIn(viewEnabled, new wxIntProperty("WPort", wxPG_LABEL, 800));
		AppendIn(viewEnabled, new wxIntProperty("HPort", wxPG_LABEL, 600));

		AppendIn(viewEnabled, new wxIntProperty("XView", wxPG_LABEL, 0));
		AppendIn(viewEnabled, new wxIntProperty("YView", wxPG_LABEL, 0));
		AppendIn(viewEnabled, new wxIntProperty("WView", wxPG_LABEL, 800));
		AppendIn(viewEnabled, new wxIntProperty("HView", wxPG_LABEL, 600));

		AppendIn(viewEnabled, new wxIntProperty("HBoarder", wxPG_LABEL, 32));
		AppendIn(viewEnabled, new wxIntProperty("VBoarder", wxPG_LABEL, 32));

		AppendIn(viewEnabled, new wxIntProperty("HSpeed", wxPG_LABEL, -1));
		AppendIn(viewEnabled, new wxIntProperty("VSpeed", wxPG_LABEL, -1));

		AppendIn(viewEnabled, new wxBoolProperty("Inherit Parent view?", wxPG_LABEL, false));

		viewEnabled->SetExpanded(false);
	}

	m_ViewsCat->Hide(true);

	// Disable the GUI while no room is loaded
	Enable(false);
}

void RMSRoomProperties::Update()
{
	if (wxGetApp().GetOpenRoom())
	{
		auto R = wxGetApp().GetOpenRoom();

		// Setup properties correctly
		SetPropertyValue("Width", R->GetWidth());
		SetPropertyValue("Height", R->GetHeight());
		SetPropertyValue("Persistent?", R->GetIsPersistent());
		SetPropertyValue("Inherit Parent setup?", R->GetInheritsBaseSettings());

		SetPropertyValue("Is Physics World?", R->GetIsPhysicsWorld());
		SetPropertyValue("Physics World Gravity X", R->GetPhysicsWorldGravityX());
		SetPropertyValue("Physics World Gravity Y", R->GetPhysicsWorldGravityX());
		SetPropertyValue("Inherit Parent physics?", R->GetInheritsPhysicsWorldSettings());

		SetPropertyValue("Enable Views?", R->GetViewsEnabled());
		SetPropertyValue("Views clear display buffer?", R->GetViewsClearDisplayBuffer());
		SetPropertyValue("Views clear background?", R->GetViewsClearBackground());
		SetPropertyValue("Inherit Parent view settings?", R->GetInheritsViewSettings());

		// Views
		for (unsigned i = 0; i < 8; i++)
		{
			wxString viewString("View " + to_string(i));
			auto V = R->GetView(i);

			SetPropertyValue(viewString, V->GetIsInherited());

			SetPropertyValue(viewString + ".XPort", V->GetXPort());
			SetPropertyValue(viewString + ".YPort", V->GetYPort());
			SetPropertyValue(viewString + ".WPort", V->GetWPort());
			SetPropertyValue(viewString + ".HPort", V->GetHPort());

			SetPropertyValue(viewString + ".XView", V->GetXView());
			SetPropertyValue(viewString + ".YView", V->GetYView());
			SetPropertyValue(viewString + ".WView", V->GetWView());
			SetPropertyValue(viewString + ".HView", V->GetHView());

			SetPropertyValue(viewString + ".HBoarder", V->GetHBoarder());
			SetPropertyValue(viewString + ".VBoarder", V->GetVBoarder());

			SetPropertyValue(viewString + ".HSpeed", V->GetHSpeed());
			SetPropertyValue(viewString + ".VSpeed", V->GetVSpeed());

			SetPropertyValue(viewString + ".Inherit Parent view?", V->GetIsInherited());
		}

		// Show categories
		m_RoomCat->Hide(false);
		m_PhysCat->Hide(false);
		m_ViewsCat->Hide(false);

		m_NRoomCat->Hide(true);

		// Enable changing values
		Enable(true);
	}
	else
	{
		// Hide categories
		m_RoomCat->Hide(true);
		m_PhysCat->Hide(true);
		m_ViewsCat->Hide(true);

		m_NRoomCat->Hide(false);

		// Disable changing values
		Enable(false);
	}
}
