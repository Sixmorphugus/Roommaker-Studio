// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Editor.h"

#include "EditorFrame.h"
#include "build.h"
#include "Project2.h"

// wx
#include <wx/progdlg.h>

using namespace std;

bool RMSEditor::OnInit()
{
	// Init the console
	RMSPlatform::Init();

	RMSPlatform::Log("RoomMaker Studio r" + to_string(RMS_BUILD));
	RMSPlatform::Log("");

	Frame = new RMSEditorFrame();
	Frame->Show(true);

	return true;
}

int RMSEditor::OnExit()
{
	RMSPlatform::DeInit();

	// wx garbage disposal deals with wx stuff

	return 0;
}

void RMSEditor::LoadGMProject(std::string ProjectPath)
{
	wxProgressDialog* dialog = new wxProgressDialog(wxT("Just a moment..."), wxT("Parsing..."), 100, Frame, wxPD_AUTO_HIDE | wxPD_APP_MODAL);

	Project2 = new GMProject2(ProjectPath, dialog);

	delete dialog;

	if (!Project2->IsValid())
	{
		wxMessageBox("Failed to load project: " + ProjectPath,
			"Project load failed", wxOK | wxICON_ERROR);

		RMS_LogWarn("Failed to load project.");
		delete Project2;
	}
}

wxIMPLEMENT_APP_CONSOLE(RMSEditor);