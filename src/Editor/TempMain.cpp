// Copyright Chris Sixsmith 2017. All Rights Reserved.

// stdlib
#include "conio.h"

// rms
#include "Platform.h"
#include "build.h"
#include "Project2.h"
#include "Folder.h"

using namespace std;

void PrintResource(GMResource* RC, unsigned Level = 0)
{
	// indents
	string Indents;

	for (unsigned i = 0; i < Level; i++)
	{
		Indents += "  ";
	}

	// Print object
	RMSPlatform::Log(Indents + "\"" + RC->GetName() + "\"");

	GMFolder* Folder = dynamic_cast<GMFolder*>(RC);

	if (Folder)
	{
		for (unsigned i = 0; i < Folder->GetNumResources(); i++)
		{
			PrintResource(Folder->GetResource(i), Level + 1);
		}
	}
}

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

		RMSPlatform::Log("");

		// Dump out the resource tree.
		for (unsigned i = 0; i < yypProject->GetNumResources(); i++)
		{
			PrintResource(yypProject->GetResource(i));
		}
	}
	else
	{
		RMS_LogWarn("! No GameMaker Studio 2 (.yyp) project file was provided, so analysis was aborted.");
	}

	RMSPlatform::Log("");

	// Fin
	if(yypProject != NULL)
		delete yypProject;

	RMSPlatform::Log("Press any key to close this window.");
	while (!kbhit()) {}

	RMSPlatform::DeInit();
}
