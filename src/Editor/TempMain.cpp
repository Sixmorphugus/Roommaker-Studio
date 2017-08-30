// Copyright Chris Sixsmith 2017. All Rights Reserved.

// stdlib
#include "conio.h"

// rapidjson


// rms
#include "Platform.h"
#include "build.h"
#include "Project2.h"

using namespace std;

// Temporary main function; Loads in Room JSON data and displays it
int main(int argc, char* argv[])
{
	RMSPlatform::Init();

	RMSPlatform::Log("RoomMaker Studio prototype r" + to_string(RMS_BUILD));
	RMSPlatform::Log("");

	GMProject2* yypProject = NULL;

	if (argc > 1)
	{
		yypProject = new GMProject2(argv[1]);
	}
	else
	{
		RMS_LogWarn("! No GameMaker Studio 2 (.yyp) project file was provided, so analysis was aborted.");
	}

	// Print some information
	RMSPlatform::Log("");

	// TODO

	// Fin
	if(yypProject != NULL)
		delete yypProject;

	RMSPlatform::Log("Press any key to close this window.");
	while (!kbhit()) {}

	RMSPlatform::DeInit();
}
