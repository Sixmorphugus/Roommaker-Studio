// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"
#include <wx/aui/aui.h>

class RMSEditorFrame : public wxFrame
{
public:
	wxAuiManager m_AuiManager;
	class RMSRoomTree* m_RoomTree;
	class RMSRoomProperties* m_RoomProperties;

public:
	RMSEditorFrame();
	~RMSEditorFrame();

	void Update();
private:
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	void OnLoadGMS2Project(wxCommandEvent& event);
	void OnSaveProject(wxCommandEvent& event);
	void OnDropProject(wxCommandEvent& event);
	void OnGithub(wxCommandEvent& event);

	void OnRoomExport(wxCommandEvent& event);

	void OnViewRoomTree(wxCommandEvent& event);
	void OnViewRoomProperties(wxCommandEvent& event);
};