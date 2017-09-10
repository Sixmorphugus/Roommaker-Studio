// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "RoomTree.h"
#include "Project2.h"
#include "Editor.h"
#include "Folder.h"
#include "Room.h"

class RMSRoomTreeItemData : public wxTreeItemData
{
private:
	GMRoom* m_Room;

public:
	RMSRoomTreeItemData() {};
	RMSRoomTreeItemData(GMRoom* Room) {
		m_Room = Room;
	};

	GMRoom* GetRoom() { return m_Room; }
	void SetRoom(GMRoom* Room) { m_Room = Room; }
};

RMSRoomTree::RMSRoomTree(wxWindow *parent, wxWindowID id /*= wxID_ANY*/, const wxPoint &pos /*= wxDefaultPosition*/, const wxSize &size /*= wxDefaultSize*/, long style /*= wxTR_DEFAULT_STYLE*/, const wxValidator &validator /*= wxDefaultValidator*/, const wxString &name /*= wxTreeCtrlNameStr*/)
	: wxTreeCtrl(parent, id, pos, size, style, validator, name)
{
	m_TreeRoot = AddRoot("Rooms");

	Bind(wxEVT_TREE_ITEM_ACTIVATED, &RMSRoomTree::OnTreeItemActivated, this);
}

void RMSRoomTree::Repopulate()
{
	RMS_LogInfo("Repopulating room tree...");

	// Clear tree
	DeleteAllItems();
	m_TreeRoot = AddRoot("Rooms");

	// Populate with rooms
	GMProject2* Proj = wxGetApp().GetProject();

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

	Expand(m_TreeRoot);
}

void RMSRoomTree::AddResource(wxTreeItemId parent, GMResource* Resource)
{
	GMRoom* Room = dynamic_cast<GMRoom*>(Resource);

	wxTreeItemId Id = AppendItem(m_TreeRoot, Resource->GetName());

	if(Room)
		SetItemData(Id, new RMSRoomTreeItemData(Room));

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

void RMSRoomTree::OnTreeItemActivated(wxTreeEvent& evt)
{
	auto ItemData = GetItemData(evt.GetItem());
	RMSRoomTreeItemData* RoomData = dynamic_cast<RMSRoomTreeItemData*>(ItemData);

	if (RoomData)
	{
		wxGetApp().SetOpenRoom(RoomData->GetRoom());
	}
}
