// Copyright Chris Sixsmith 2017. All Rights Reserved.

// stdlib
#include "conio.h"

// rms
#include "Platform.h"
#include "build.h"

using namespace std;

// Temporary main function; Loads in Room JSON data and displays it
int main(int argc, char* argv[])
{
	RMSPlatform::Init();

	RMSPlatform::Log("RoomMaker Studio prototype r" + std::to_string(RMS_BUILD));
	RMSPlatform::Log("");

	if (argc > 1)
	{

	}
	else
	{
		RMS_LogWarn("! No GameMaker Studio 2 (.yyp) project file was provided, so analysis was aborted.");
		RMSPlatform::Log("");
	}

	RMSPlatform::Log("Press any key to close this window.");
	while (!kbhit()) {}

	RMSPlatform::DeInit();
}
