// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "EditorFrame.h"
#include "Editor.h"
#include "build.h"
#include "SFMLCanvas.h"

#include <wx/filedlg.h>

using namespace std;

enum
{
	rmsID_LoadGMS2Project
};

RMSEditorFrame::RMSEditorFrame()
	: wxFrame(NULL, wxID_ANY, "Roommaker Studio r" + to_string(RMS_BUILD))
{
	// Init window
	Maximize(true);

	// Add the Menu Bar
	wxMenu *menuFile = new wxMenu;
	
	menuFile->Append(rmsID_LoadGMS2Project, "Load GMS2 Project File...", "Load the GMS2 project file you're going to be working with.");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

	// Add the Status Bar
	CreateStatusBar();
	SetStatusText("Welcome to RMS!");

	// Add the Room View
	wxBoxSizer* BS = new wxBoxSizer(wxHORIZONTAL);

	rmsSFMLCanvas* Canvas = new rmsSFMLCanvas(this, wxID_ANY);
	BS->Add(Canvas, wxALL|wxEXPAND);

	BS->Layout();

	// Bind events
	Bind(wxEVT_MENU, &RMSEditorFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &RMSEditorFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &RMSEditorFrame::OnLoadGMS2Project, this, rmsID_LoadGMS2Project);
}

void RMSEditorFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void RMSEditorFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is Roommaker Studio; a lightweight GameMaker Studio 2 room editor.\nPlease do let me know if you find any issues with the software!",
		"About Roommaker Studio", wxOK | wxICON_INFORMATION);
}

void RMSEditorFrame::OnLoadGMS2Project(wxCommandEvent& event)
{
	/*
	if (...current content has not been saved...)
	{
		if (wxMessageBox(_("Current project has not been saved! Proceed?"), _("Please confirm"),
			wxICON_QUESTION | wxYES_NO, this) == wxNO)
			return;
		//else: proceed asking to the user the new file to open
	}
	*/

	wxFileDialog
		openFileDialog(this, _("Load GMS2 Project File"), "", "",
			"YYP files (*.yyp)|*.yyp", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return; // the user changed idea...

	// proceed loading the file chosen by the user
	wxGetApp().LoadGMProject(openFileDialog.GetPath().ToStdString());
}
