// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"

class GMProject2;

class RMSDLL RMSEditor : public wxApp
{
private:
	GMProject2* Project2;
	class RMSEditorFrame* Frame;

private:
	virtual bool OnInit();
	virtual int OnExit();

public:
	void LoadGMProject(std::string ProjectPath);

	GMProject2* GetGMProject() { return Project2; }
	bool IsGMProjectLoaded() { return Project2 != NULL; }

	RMSEditorFrame* GetFrame() { return Frame; }
};

wxDECLARE_APP(RMSEditor);