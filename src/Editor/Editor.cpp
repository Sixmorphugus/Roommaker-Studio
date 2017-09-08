// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Editor.h"

#include <string>
#include "build.h"

using namespace std;

bool RMSEditor::OnInit()
{
	// Init the console
	RMSPlatform::Init();

	RMSPlatform::Log("RoomMaker Studio prototype r" + to_string(RMS_BUILD));
	RMSPlatform::Log("");

	return true;
}

int RMSEditor::OnExit()
{
	RMSPlatform::DeInit();

	return 0;
}

wxIMPLEMENT_APP_CONSOLE(RMSEditor);