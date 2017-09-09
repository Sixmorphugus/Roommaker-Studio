// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "RoomTree.h"
#include "Project2.h"
#include "Editor.h"
#include "Folder.h"

rmsRoomTree::rmsRoomTree(wxWindow *parent, wxWindowID id /*= wxID_ANY*/, const wxPoint &pos /*= wxDefaultPosition*/, const wxSize &size /*= wxDefaultSize*/, long style /*= wxTR_DEFAULT_STYLE*/, const wxValidator &validator /*= wxDefaultValidator*/, const wxString &name /*= wxTreeCtrlNameStr*/)
	: wxTreeCtrl(parent, id, pos, size, style, validator, "Rooms")
{
	m_TreeRoot = AddRoot("Rooms");
}

void rmsRoomTree::Repopulate()
{
	RMS_LogInfo("Repopulating room tree...");

	// Clear tree
	DeleteAllItems();
	m_TreeRoot = AddRoot("Rooms");

	// Populate with rooms
	GMProject2* Proj = wxGetApp().GetGMProject();

	if (Proj)
	{
		GMResource* Rooms = Proj->GetResourceByName("rooms");
		GMFolder* RoomsFolder = dynamic_cast<GMFolder*>(Rooms);

		if (RoomsFolder)
		{
			for (unsigned i = 0; i < RoomsFolder->GetNumResources(); i++)
			{
				auto Resource = RoomsFolder->GetResource(i);

				AddResource(m_TreeRoot, Resource);
			}
		}
		else
		{
			RMS_LogWarn("No rooms folder!");
		}
	}
	else
	{
		RMS_LogInfo("No project present, nevermind...");
	}
}

void rmsRoomTree::AddResource(wxTreeItemId parent, GMResource* Resource)
{
	wxTreeItemId Id = AppendItem(m_TreeRoot, Resource->GetName());

	GMFolder* FolderResource = dynamic_cast<GMFolder*>(Resource);
	if (FolderResource)
	{
		for (unsigned i = 0; i < FolderResource->GetNumResources(); i++)
		{
			auto Resource = FolderResource->GetResource(i);

			AddResource(Id, Resource);
		}
	}
}
