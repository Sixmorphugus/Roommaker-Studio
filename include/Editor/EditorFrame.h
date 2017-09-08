// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"

class RMSEditorFrame : public wxFrame
{
public:
	RMSEditorFrame();
private:
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	void OnLoadGMS2Project(wxCommandEvent& event);
};