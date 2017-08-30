// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "PlatformDeduction.h"

namespace RMSPlatform {
	enum LOGTYPE { INF = 0, WARNING = 1, FATAL = 2, CHAISCRIPT = 3 };

	RMSDLL bool Init();
	RMSDLL void DeInit();

	RMSDLL void Update();

	RMSDLL void ShowMessageBox(std::string caption, std::string text, bool showErrorIcon = false);

	RMSDLL void WriteToLogfile(std::string info);
	RMSDLL void WriteToConsole(std::string info, unsigned int color = 0);

	RMSDLL void Log(std::string info, bool nl = true);
	RMSDLL void DiagnosticLog(LOGTYPE type, std::string file, std::string func, int line, std::string info, bool nl = true);
	RMSDLL void DiagnosticError(std::string file, std::string func, int line, std::string info);

	RMSDLL std::vector<std::string> DirList(std::string path, bool includeExtra = false);
	RMSDLL std::string RealPath(std::string path);
	RMSDLL bool FileDelete(std::string in);

	RMSDLL bool SetWorkDir(std::string path);
	RMSDLL void ResetWorkDir();
	RMSDLL std::string GetWorkDir();

	RMSDLL bool GetConsoleInput(std::string &input);
	RMSDLL void ClearConsoleInput(bool eraseCompletely = true);
	RMSDLL std::string GetLastLogged();

	RMSDLL bool LoadTextFile(std::string & fileData, const std::string& fileName);
	RMSDLL bool SaveTextFile(const std::string & fileData, const std::string & fileName);
}

// macros
#ifdef _MSC_VER

#define RMS_LogInfo(string) RMSPlatform::DiagnosticLog(RMSPlatform::INF, __FILE__, __FUNCTION__, __LINE__, string);
#define RMS_LogWarn(string) RMSPlatform::DiagnosticLog(RMSPlatform::WARNING, __FILE__, __FUNCTION__, __LINE__, string);
#define RMS_LogFatal(string) RMSPlatform::DiagnosticError(__FILE__, __FUNCTION__, __LINE__, string);

#else

#define RMS_LogInfo(string) RMSPlatform::DiagnosticLog(RMSPlatform::INF, __FILE__, __func__, __LINE__, string);
#define RMS_LogWarn(string) RMSPlatform::DiagnosticLog(RMSPlatform::WARNING, __FILE__, __func__, __LINE__, string);
#define RMS_LogFatal(string) RMSPlatform::DiagnosticError(__FILE__, __func__, __LINE__, string);

#endif