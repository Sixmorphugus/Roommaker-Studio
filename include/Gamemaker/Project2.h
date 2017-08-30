// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"
#include "GM.h"

#include <memory>

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
	GMProject2(std::string ProjectPath);

	std::string GetProjectPath() { return m_ProjectPath; }
	bool IsValid() { return m_Valid; }

	// Begin GMResourceContainer Interface
	virtual unsigned GetNumResources();
	virtual GMResource* GetResource(unsigned i);
	// End
};