// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"
#include <wx/propgrid/propgrid.h>

class RMSDLL RMSRoomProperties : public wxPropertyGrid
{
private:
	wxPGProperty* m_NRoomCat;

	wxPGProperty* m_RoomCat;
	wxPGProperty* m_PhysCat;
	wxPGProperty* m_ViewsCat;

public:
	RMSRoomProperties(wxWindow *parent, wxWindowID id = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxPG_DEFAULT_STYLE,
		const wxString& name = "Room Properties");

	void Update();
};