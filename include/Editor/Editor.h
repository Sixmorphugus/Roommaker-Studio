// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"

class GMProject2;

class RMSDLL RMSEditor : public wxApp
{
private:
	GMProject2* m_Project2;
	bool m_ProjectDirty;
	class RMSEditorFrame* m_Frame;

private:
	virtual bool OnInit();
	virtual int OnExit();

public:
	void LoadGMS2Project(std::string ProjectPath);
	void DropProject();

	GMProject2* GetGMProject() { return m_Project2; }
	bool IsProjectLoaded() { return m_Project2 != NULL; }
	bool IsProjectDirty() { return m_ProjectDirty; }
	void MakeProjectDirty() { m_ProjectDirty = true; }

	void SaveProject();

	RMSEditorFrame* GetFrame() { return m_Frame; }
};

wxDECLARE_APP(RMSEditor);