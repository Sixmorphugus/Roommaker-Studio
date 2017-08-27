// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Platform.h"

#ifdef RMS_PLATFORM_WINDOWS

#include <windows.h>
#include <direct.h>
#include <fstream>
#include <iostream>
#include "SFML/System.hpp"

using namespace std;

// internal stuff
FILE *cstream;
ofstream file;

string consoleInputBuffer, consoleInputBuffer2;
bool consoleInputOffset;
bool consoleInputWaiting;
bool consoleInputOnScreen;
int consoleHistoryLocation;
vector<string> consoleHistory;
string defaultWorkDir;

HANDLE hStdOut;
HANDLE hStdIn;

void ConsoleErase(unsigned int num, bool eraseAndRepeat = true)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD cursorPosition;
	COORD cursorPositionNew;

	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	cursorPosition = csbi.dwCursorPosition;

	cursorPositionNew = cursorPosition;
	cursorPositionNew.X -= num;

	while (cursorPositionNew.X < 0)
	{
		cursorPositionNew.X += csbi.dwSize.X;
		cursorPositionNew.Y -= 1;
	}

	SetConsoleCursorPosition(hStdOut, cursorPositionNew);

	if (eraseAndRepeat)
	{
		for(unsigned int i = 0; i < num; i++)
			cout << " ";

		ConsoleErase(num, false);
	}
}

bool RMSPlatform::Init()
{
	// redirect stderr to the console.log file
	if (freopen_s(&cstream, "console.log", "w", stderr) != 0)
	{
		ShowMessageBox("Can't start!", "The game files already seem to be in use.\nDid you run the game twice?\n\nWill abort.");
		abort();
	}

	RMS_LogInfo("Working in " + RealPath("."));
	defaultWorkDir = RealPath(".");

	// turn off sf::err
	file = ofstream("sfml.log");
	sf::err().rdbuf(file.rdbuf());

	// ...init any windows stuff we need later...
	consoleInputOffset = true;
	consoleInputWaiting = false;
	consoleInputOnScreen = false;
	consoleHistoryLocation = 0;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdIn = GetStdHandle(STD_INPUT_HANDLE);

	return true;
}

void RMSPlatform::DeInit() {
	// close the console log file
	fclose(cstream);
	file.close();
}

void RMSPlatform::Update() {
	// This is mostly code I wrote in 2014.
	// I'm so sorry.

	// It was originally written for the conio.h library, a library that is heavily depreciated and only still included in systems for
	// historical (hysterical) reasons.
	// This version of the code is adapted for Windows.h.

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut, &csbi);

	if (consoleInputOffset)
	{
		cout << "> " << consoleInputBuffer;
		consoleInputOffset = false;
		consoleInputOnScreen = true;
	}

	// Find out how many console events have happened:
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	GetNumberOfConsoleInputEvents(hStdIn, &numEvents);

	if (numEvents != 0)
	{
		// Create a buffer of that size to store the events
		INPUT_RECORD *eventBuffer = new INPUT_RECORD[numEvents];

		// Read the console events into that buffer, and save how
		// many events have been read into numEventsRead.
		ReadConsoleInputA(hStdIn, eventBuffer, numEvents, &numEventsRead);

		for (DWORD i = 0; i < numEventsRead; ++i)
		{
			// Check the event type: was it a key?
			if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown)
			{
				char logIn = eventBuffer[i].Event.KeyEvent.uChar.AsciiChar; // key that was hit
				int specialId = (int)logIn; // ascii id of that key

				if (specialId > 31 && specialId < 127)
				{ // these are our whitelisted letters
					cout << logIn;
					consoleInputBuffer = consoleInputBuffer + (char)logIn;
				}
				else if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_BACK) // backspace
				{
					if (consoleInputBuffer.size() > 0)
					{
						ConsoleErase(1);

						// now we just remove the last char of our _inBuff
						consoleInputBuffer = consoleInputBuffer.substr(0, consoleInputBuffer.size() - 1);
					}
				}
				else if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
				{
					// log user's input and start a new line
					cout << "\n";
					consoleInputOffset = true;

					consoleInputBuffer2 = consoleInputBuffer;
					consoleInputWaiting = true;

					WriteToLogfile("> " + consoleInputBuffer2 + "\n");

					// update the history
					if (consoleHistory.size() > 0) {
						if (consoleHistory[consoleHistory.size() - 1] != consoleInputBuffer2) {
							consoleHistory.push_back(consoleInputBuffer2);
						}
					}
					else {
						consoleHistory.push_back(consoleInputBuffer2);
					}

					consoleHistoryLocation = consoleHistory.size(); // set history loc to 1 more than the array size						
					consoleInputBuffer = ""; // clear buffer

					consoleInputOnScreen = false;
				}
				else if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_UP)
				{
					// can we go up through the history
					if (consoleHistoryLocation - 1 > -1)
					{
						ClearConsoleInput(false);

						consoleHistoryLocation -= 1;
						consoleInputBuffer = consoleHistory[consoleHistoryLocation];
					}
				}
				else if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
				{
					// can we go down through the history
					if (consoleHistoryLocation + 1 >= consoleHistory.size())
					{
						ClearConsoleInput(false);

						consoleHistoryLocation = consoleHistory.size();
						consoleInputBuffer = "";
					}
					else
					{
						ClearConsoleInput(false);

						consoleHistoryLocation += 1;
						consoleInputBuffer = consoleHistory[consoleHistoryLocation];
					}
				}
			}
		}
	}
}

void RMSPlatform::WriteToLogfile(string in)
{
	FILE* st = stderr;
	fputs(in.c_str(), st);

	file.flush();
}

void RMSPlatform::WriteToConsole(string in, unsigned int color)
{
	ClearConsoleInput(false);
	
	const WORD colors[] =
	{
		15, 3, 12, 7
	};

	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut, &csbi);

	// Set current color
	SetConsoleTextAttribute(hStdOut, colors[color]);

	cout << in;

	// Keep users happy
	SetConsoleTextAttribute(hStdOut, csbi.wAttributes);
}

void RMSPlatform::ShowMessageBox(string caption, string text, bool showErrorIcon)
{
	// sf string
	sf::String c(caption);
	sf::String t(text);

	MessageBoxW(nullptr, t.toWideString().c_str(), c.toWideString().c_str(), showErrorIcon ? MB_ICONSTOP : MB_ICONINFORMATION);
}

vector<string> RMSPlatform::DirList(string path, bool includeExtra)
{
	vector<string> resultsVec;

	HANDLE hFind;
	WIN32_FIND_DATAW data;

	// use sf string for conversion
	sf::String pathSf(path);

	hFind = FindFirstFileW((pathSf + "/*.*").toWideString().c_str(), &data);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			resultsVec.push_back(sf::String(data.cFileName));
		} while (FindNextFileW(hFind, &data));
		FindClose(hFind);
	}
	else
	{
		RMS_LogInfo("INVALID_HANDLE_VALUE while executing windows dirList. Nothing will be returned.");
	}

	if (resultsVec.size() > 0)
	{
		resultsVec.erase(resultsVec.begin());
		resultsVec.erase(resultsVec.begin());
	}

	// move anything with no extension to the top of the list
	unsigned int numFolders = 0;
	for (unsigned int i = 0; i < resultsVec.size(); i++)
	{
		if (resultsVec[i].find(".") == string::npos)
		{
			string f = resultsVec[i];

			resultsVec.erase(resultsVec.begin() + i);
			resultsVec.insert(resultsVec.begin(), f);

			numFolders += 1;
			i = numFolders;
		}
	}

	if (includeExtra)
	{
		resultsVec.insert(resultsVec.begin(), "..");
	}

	return resultsVec;
}

string RMSPlatform::RealPath(string in)
{
	WCHAR buffer[4250];
	WCHAR** lppPart = { NULL };

	sf::String i(in);
	
	GetFullPathNameW(i.toWideString().c_str(), 4250, buffer, lppPart);

	return sf::String(buffer).toAnsiString();
}

bool RMSPlatform::FileDelete(string in)
{
	sf::String i(in);

	bool r = DeleteFileW(i.toWideString().c_str());

	string errstring;

	switch (GetLastError())
	{
	default:
		errstring = "Unknown Error";
		break;
	case ERROR_FILE_NOT_FOUND:
		errstring = "File Not Found";
		break;
	case ERROR_ACCESS_DENIED:
		errstring = "Permission Denied";
		break;
	case ERROR_INVALID_NAME:
		errstring = "Bad name";
		break;
	}

	if (!r)
	{
		RMS_LogWarn("Can't delete: " + in + " (" + errstring + ")");
	}

	return r;
}

bool RMSPlatform::GetConsoleInput(string & input)
{
	if (consoleInputWaiting)
	{
		input = consoleInputBuffer2;
		consoleInputWaiting = false;

		return true;
	}

	return false;
}

void RMSPlatform::ClearConsoleInput(bool eraseCompletely)
{
	if (!consoleInputOnScreen)
		return;

	ConsoleErase(consoleInputBuffer.size());

	// overwrite any "> " that might exist in the consoleManager readout
	ConsoleErase(2);

	consoleInputOnScreen = false;

	if (eraseCompletely)
	{
		consoleInputBuffer = "";
	}
	else
	{
		consoleInputOffset = true;
	}
}

bool RMSPlatform::SetWorkDir(string path)
{
	path = RealPath(path);

	bool s = chdir(path.c_str()) == 0;

	if (!s)
	{
		RMS_LogWarn("Unable to work in directory \"" + path + "\"!");
	}

	return s;
}

void RMSPlatform::ResetWorkDir()
{
	SetWorkDir(defaultWorkDir);
}

string RMSPlatform::GetWorkDir()
{
	const size_t max = 1024;
	char buf[max];
	getcwd(buf, max);

	return string(buf);
}


#endif
