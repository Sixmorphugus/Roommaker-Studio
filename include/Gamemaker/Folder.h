// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "GM.h"

class RMSDLL GMFolder :
	public GMResource, public GMResourceContainer
{
private:
	std::vector<GMResource*> m_Resources;
	GMResourceType m_FilterType;
	bool m_DefaultFolder;

public:
	// Load a folder from views.
	GMFolder(GMProject2* Project, std::string Key, std::string DataPath);

	virtual void Init();

	unsigned GetNumResources() { return m_Resources.size(); }
	GMResource* GetResource(unsigned i) { return m_Resources[i]; }
	virtual GMResourceType GetType() { return Folder; }
	virtual GMResourceType GetFilterType() { return m_FilterType; }
	bool IsDefaultFolder() { return m_DefaultFolder; }
};