// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Editor.h"

#include "EditorFrame.h"
#include "build.h"
#include "Project2.h"
#include "Room.h"

// wx
#include <wx/progdlg.h>

using namespace std;

bool RMSEditor::OnInit()
{
	// Init the console
	RMSPlatform::Init();

	RMSPlatform::Log("RoomMaker Studio r" + to_string(RMS_BUILD));
	RMSPlatform::Log("");

	m_Project2 = NULL;
	m_ProjectDirty = false;

	m_OpenRoom = NULL;

	m_Frame = new RMSEditorFrame();
	m_Frame->Show(true);

	return true;
}

int RMSEditor::OnExit()
{
	RMSPlatform::DeInit();

	// wx garbage disposal deals with wx stuff

	return 0;
}

void RMSEditor::LoadGMS2Project(std::string ProjectPath)
{
	wxProgressDialog* dialog = new wxProgressDialog(wxT("Just a moment..."), wxT("Parsing..."), 100, m_Frame, wxPD_AUTO_HIDE | wxPD_APP_MODAL);

	m_Project2 = new GMProject2(ProjectPath, dialog);

	delete dialog;

	if (!m_Project2->IsValid())
	{
		wxMessageBox("Failed to load project: " + ProjectPath,
			"Project load failed", wxOK | wxICON_ERROR);

		RMS_LogWarn("Failed to load project.");
		delete m_Project2;
	}

	m_ProjectDirty = false;
	m_OpenRoom = NULL;
}

void RMSEditor::DropProject()
{
	delete m_Project2;
	m_Project2 = NULL;
	m_OpenRoom = NULL;

	m_ProjectDirty = false;
}

void RMSEditor::SaveProject()
{
	m_ProjectDirty = false;

	if(m_Project2)
		m_Project2->Save();
}

void RMSEditor::SetOpenRoom(GMRoom* OpenRoom)
{
	m_OpenRoom = OpenRoom;
	RMS_LogInfo("Opening Room: \"" + OpenRoom->GetName() + "\"");

	m_Frame->Update();
}

wxIMPLEMENT_APP_CONSOLE(RMSEditor);