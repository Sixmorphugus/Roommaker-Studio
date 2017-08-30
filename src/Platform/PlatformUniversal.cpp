// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "platform.h"
#include <fstream>

using namespace std;

string lastLogged;

string RMSPlatform::GetLastLogged() {
	return lastLogged;
}

void RMSPlatform::Log(string info, bool nl)
{
	// Message
	WriteToLogfile(info);
	WriteToConsole(info, 3);

	// Line terminator
	if (nl) {
		WriteToLogfile("\n");
		WriteToConsole("\n", 3);
	}
}

void RMSPlatform::DiagnosticLog(LOGTYPE type, string file, string func, int line, string info, bool nl)
{
	string typewords[] = { "INFO", "WARNING", "FATAL", "CHAISCRIPT" };

	// Level and source code information
	#ifdef _DEBUG
	WriteToLogfile(typewords[type] + "[" + file + ":" + to_string(line) + " (" + func + ")]: " + info + (nl ? "\n" : ""));
	#else
	WriteToLogfile(type + "[unavailable]: " + info + (nl ? "\n" : ""));
	#endif

	lastLogged = info;

	WriteToConsole(info + (nl ? "\n" : ""), type);
}

void RMSPlatform::DiagnosticError(string file, string func, int line, string info)
{
	DiagnosticLog(FATAL, file, func, line, info, true);

	// show a message to the user
	ShowMessageBox("RoomMaker Studio has crashed!", info + " (" + func + ")", true);

	// make sure not to forget the console info
	DeInit();

	// crash
	abort();
}

bool RMSPlatform::LoadTextFile(string & fileData, const string& fileName)
{
	ifstream is(fileName);

	if (is.bad())
		return false;

	string str((istreambuf_iterator<char>(is)), istreambuf_iterator<char>());
	is.close();

	fileData = str;

	return true;
}

bool RMSPlatform::SaveTextFile(const string & fileData, const string & fileName)
{
	ofstream os(fileName);

	if (os.bad())
		return false;

	os << fileData;
	os.close();

	return true;
}