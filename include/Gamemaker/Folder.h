// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "GM.h"

class RMSDLL GMFolder :
	public GMResource, public GMResourceContainer
{
private:
	std::vector<GMResource*> m_Resources;

public:
	GMFolder(GMProject2* Project, std::string Key, std::string DataPath);

	unsigned GetNumResources() { return m_Resources.size(); }
	GMResource* GetResource(unsigned i) { return m_Resources[i]; }
};