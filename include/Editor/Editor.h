// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"

class GMProject2;
class GMRoom;

class RMSDLL RMSEditor : public wxApp
{
private:
	GMProject2* m_Project2;
	GMRoom* m_OpenRoom;
	bool m_ProjectDirty;
	class RMSEditorFrame* m_Frame;

private:
	virtual bool OnInit();
	virtual int OnExit();

public:
	void LoadGMS2Project(std::string ProjectPath);
	void DropProject();

	GMProject2* GetProject() { return m_Project2; }
	bool IsProjectLoaded() { return m_Project2 != NULL; }
	bool IsProjectDirty() { return m_ProjectDirty; }
	void MakeProjectDirty() { m_ProjectDirty = true; }

	void SaveProject();

	RMSEditorFrame* GetFrame() { return m_Frame; }

	GMRoom* GetOpenRoom() { return m_OpenRoom; }
	void SetOpenRoom(GMRoom* OpenRoom);
};

wxDECLARE_APP(RMSEditor);