#include "Platform.h"

#ifdef RMS_PLATFORM_LINUX

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <string>

using namespace std;

// namespace stuff
FILE *cstream;
ofstream file;
string defaultWorkDir;

// linux, for the most part, was not our development platform.
// Later, the console might work properly. As of now it can only print things.

bool RMSPlatform::Init()
{
	// redirect stderr to the console.log file
	cstream = freopen("console.log", "w", stderr);

	// turn off sf::err
	file.open("sfml.log");
	sf::err().rdbuf(file.rdbuf());

	// ...init any linux stuff we need later...
	defaultWorkDir = getWorkDir();

	// show a warning
	//showMessageBox("Disclaimer", "The linux version of SUPER_ALCHEMIST is still very much work in progress; features may be broken or missing, and the game can do odd things.\nIf you're ok with that, feel free to continue!");

	return true;
}

void RMSPlatform::DeInit()
{
	// close the console log
	fclose(cstream);
	file.flush();
}

void RMSPlatform::Update()
{

}

void RMSPlatform::WriteToLogfile(string in)
{
	FILE* st = stderr;
	fputs(in.c_str(), st);

	file.flush();
}

void RMSPlatform::WriteToConsole(string in, unsigned int color)
{
	string colorData[] = { "/026[30m" };

	color = 0;

	cout << colorData[color] << in;
}

void RMSPlatform::ShowMessageBox(string caption, string text, bool showErrorIcon)
{
	// uses zenity; if this isn't available on the system, no message box will appear.
	string zenityString = "zenity --info --text=\"" + text + "\" --title=\"" + caption + "\"";
	FILE * f = popen(zenityString.c_str(), "r" );
	pclose( f );
}

vector<string> RMSPlatform::DirList(string path, bool includeExtra)
{
	vector<string> resultsVec;

	DIR *dp;
	struct dirent *dirp;
	if((dp  = opendir(("./" + path).c_str())) == NULL)
	{
		info("Unable to read linux directory " + path);
	}
	else {
        while ((dirp = readdir(dp)) != NULL)
		{
			string nString = string(dirp->d_name);

			if ((nString != "." && nString != ".."))
				resultsVec.push_back(nString);
        }

        closedir(dp);
	}

	if (includeExtra)
		resultsVec.insert(resultsVec.begin(), "..");

	return resultsVec;
}

string RMSPlatform::RealPath(string in)
{
    return realpath(in.c_str(), NULL);
}

bool RMSPlatform::FileDelete(string in)
{
	return remove(in.c_str()) == 0;
}

bool RMSPlatform::GetConsoleInput(string &input)
{
    return false;
}

void RMSPlatform::ClearConsoleInput(bool eraseCompletely)
{

}

bool RMSPlatform::SetWorkDir(string path)
{
	path = realPath(path);

	bool s = chdir(path.c_str()) == 0;

	if (!s) {
		warn("Unable to work in directory \"" + path + "\"!");
	}

	return s;
}

void RMSPlatform::ResetWorkDir()
{
	setWorkDir(defaultWorkDir);
}

string RMSPlatform::GetWorkDir()
{
	const size_t max = 1024;
	char buf[max];
	getcwd(buf, max);

	return string(buf);
}

#endif
