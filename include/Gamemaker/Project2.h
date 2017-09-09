// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"
#include "GM.h"

#include <memory>

class wxProgressDialog;

/*
 Roommaker Studio GMS2 project mirroring
 */
class RMSDLL GMProject2 :
	public GMResourceContainer
{
private:
	bool m_Valid;
	std::string m_ProjectPath;

	std::vector<std::shared_ptr<GMResource>> m_Resources;
	std::vector<GMResource*> m_ResourcesTopLevel;

private:
	void LoadResource(std::string Key, std::string RelativePath, GMResourceType Type);

public:
	GMProject2(std::string ProjectPath, wxProgressDialog* ProgDlg = NULL);

	std::string GetProjectPath() { return m_ProjectPath; }
	std::string GetProjectRoot();
	bool IsValid() { return m_Valid; }

	GMResource* FindResource(std::string m_Key);

	// Begin GMResourceContainer Interface
	virtual unsigned GetNumResources();
	virtual GMResource* GetResource(unsigned i);
	// End

	void Save();

	friend class GMResourceContainer; // For book-keeping reasons, GMResourceContainer can access the private resource list.
};
