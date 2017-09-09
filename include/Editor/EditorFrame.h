// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"
#include <wx/aui/aui.h>

class RMSEditorFrame : public wxFrame
{
public:
	wxAuiManager m_AuiManager;
	class rmsRoomTree* m_RoomTree;

public:
	RMSEditorFrame();
	~RMSEditorFrame();
private:
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	void OnLoadGMS2Project(wxCommandEvent& event);
	void OnSaveProject(wxCommandEvent& event);
	void OnDropProject(wxCommandEvent& event);
	void OnGithub(wxCommandEvent& event);

	void OnRoomExport(wxCommandEvent& event);

	void OnViewRoomTree(wxCommandEvent& event);
};