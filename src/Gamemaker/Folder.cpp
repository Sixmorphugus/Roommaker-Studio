#include "Folder.h"

using namespace std;

GMFolder::GMFolder(GMProject2* Project, string Key, string DataPath)
	: GMResource(Project, Key, DataPath)
{
	vector<string> ChildIDs;

	// Let's read our datafile:
	RMSPlatform::Log("\t\tReal path is " + GetRealPath());
}

