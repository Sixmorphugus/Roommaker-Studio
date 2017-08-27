// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Platform.h"
#include "build.h"
#include "conio.h"

using namespace std;

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