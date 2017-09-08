// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "RoomTree.h"

rmsRoomTree::rmsRoomTree(wxWindow *parent, wxWindowID id /*= wxID_ANY*/, const wxPoint &pos /*= wxDefaultPosition*/, const wxSize &size /*= wxDefaultSize*/, long style /*= wxTR_DEFAULT_STYLE*/, const wxValidator &validator /*= wxDefaultValidator*/, const wxString &name /*= wxTreeCtrlNameStr*/)
	: wxTreeCtrl(parent, id, pos, size, style, validator, "Rooms")
{
	// Populate with rooms
}
