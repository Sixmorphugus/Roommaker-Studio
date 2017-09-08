// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "EditorFrame.h"
#include "Editor.h"
#include "build.h"
#include "RoomViewer.h"

#include <wx/filedlg.h>

using namespace std;

enum
{
	rmsID_LoadGMS2Project,
	rmsID_SaveProject,
	rmsID_DropProject,
	rmsID_Github
};

RMSEditorFrame::RMSEditorFrame()
	: wxFrame(NULL, wxID_ANY, "Roommaker Studio r" + to_string(RMS_BUILD), wxDefaultPosition, wxSize(1200, 720))
{
	// Init window
	Maximize(true);

	// Add the Menu Bar
	wxMenu *menuFile = new wxMenu;
	
	menuFile->Append(rmsID_LoadGMS2Project, "Load GMS2 Project File...", "Load the GMS2 project file you're going to be working with.");
	menuFile->Append(rmsID_SaveProject, "Save Project File", "Save the project where you loaded it from.");
	menuFile->AppendSeparator();
	menuFile->Append(rmsID_DropProject, "Drop Loaded Project", "Clear out the workspace.");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	menuHelp->Append(rmsID_Github, "Github Page", "View the Roommaker Studio Github page.");

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&Project");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

	// Add the Status Bar
	CreateStatusBar();
	SetStatusText("Welcome to RMS!");

	// Add the Room View
	wxBoxSizer* BS = new wxBoxSizer(wxHORIZONTAL);

	rmsSFMLCanvas* Canvas = new rmsRoomViewer(this, wxID_ANY);
	BS->Add(Canvas, wxALL|wxEXPAND);

	BS->Layout();

	// Add the object tree


	// Bind events
	Bind(wxEVT_MENU, &RMSEditorFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &RMSEditorFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &RMSEditorFrame::OnLoadGMS2Project, this, rmsID_LoadGMS2Project);
	Bind(wxEVT_MENU, &RMSEditorFrame::OnSaveProject, this, rmsID_SaveProject);
	Bind(wxEVT_MENU, &RMSEditorFrame::OnDropProject, this, rmsID_DropProject);
	Bind(wxEVT_MENU, &RMSEditorFrame::OnGithub, this, rmsID_Github);
}

void RMSEditorFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void RMSEditorFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is Roommaker Studio; a lightweight GameMaker Studio 2 room editor.\
\nPlease do let me know if you find any issues with the software! See Help->Github Page.\
\n\nRoommaker Studio is not affiliated with YoYo Games or any of the Gamemaker Studio products; it is an external, independently developed tool.\
\n\nCopyright Chris Sixsmith 2017. All Rights Reserved.",
		"About Roommaker Studio", wxOK | wxICON_INFORMATION);
}

void RMSEditorFrame::OnLoadGMS2Project(wxCommandEvent& event)
{
	if (wxGetApp().IsProjectDirty())
	{
		if (wxMessageBox(_("Current project has not been saved! Proceed?"), _("Please confirm"),
			wxICON_QUESTION | wxYES_NO, this) == wxNO)
			return;
		//else: proceed asking to the user the new file to open
	}

	wxFileDialog
		openFileDialog(this, _("Load GMS2 Project File"), "", "",
			"YYP files (*.yyp)|*.yyp", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return; // the user changed idea...

	// proceed loading the file chosen by the user
	wxGetApp().LoadGMS2Project(openFileDialog.GetPath().ToStdString());
}

void RMSEditorFrame::OnSaveProject(wxCommandEvent& event)
{
	if (!wxGetApp().IsProjectLoaded())
	{
		wxMessageBox("No project is loaded!", "Oops!", wxOK);
		return;
	}

	wxGetApp().SaveProject();
}

void RMSEditorFrame::OnDropProject(wxCommandEvent& event)
{
	if (!wxGetApp().IsProjectLoaded())
	{
		wxMessageBox("No project is loaded!", "Oops!", wxOK);
		return;
	}

	if (wxGetApp().IsProjectDirty())
	{
		if (wxMessageBox(_("The project has not been saved! Proceed?"), _("Please confirm"),
			wxICON_QUESTION | wxYES_NO, this) == wxNO)
			return;
		//else: proceed asking to the user the new file to open
	}

	wxGetApp().DropProject();
}

void RMSEditorFrame::OnGithub(wxCommandEvent& event)
{
	wxLaunchDefaultBrowser("https://github.com/Sixmorphugus/Roommaker-Studio");
}
