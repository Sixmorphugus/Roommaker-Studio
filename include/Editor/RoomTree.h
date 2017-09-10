// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"
#include "wx/treectrl.h"

class RMSRoomTree : public wxTreeCtrl
{
private:
	wxTreeItemId m_TreeRoot;

public:
	RMSRoomTree(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxTR_DEFAULT_STYLE, const wxValidator &validator = wxDefaultValidator, const wxString &name = "Rooms");

	void Repopulate();
	void AddResource(wxTreeItemId parent, class GMResource* Resource);

	void OnTreeItemActivated(wxTreeEvent& evt);

private:
	
};