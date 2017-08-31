// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "GM.h"
#include "Project2.h"

using namespace std;

GMResource::GMResource(GMProject2* Project, string Key, string DataPath)
{
	m_Key = Key;
	m_DataPath = DataPath;
	m_Project = Project;
	m_Parent = Project;
	m_Name = "N/A";
}

GMProject2 * GMResource::GetProject()
{
	return m_Project;
}

GMResourceContainer* GMResource::GetParent()
{
	return m_Parent;
}

std::string GMResource::GetRealPath()
{
	return m_Project->GetProjectRoot() + "/" + m_DataPath;
}

bool GMResourceContainer::HasChild(string Key)
{
	for (unsigned i = 0; i < GetNumResources(); i++)
	{
		if (GetResource(i)->GetKey() == Key)
			return true;
	}

	return false;
}

bool GMResourceContainer::HasChild(GMResource* Memory)
{
	for (unsigned i = 0; i < GetNumResources(); i++)
	{
		if (GetResource(i) == Memory)
			return true;
	}

	return false;
}

void GMResourceContainer::Parent(GMResource* Memory)
{
	Memory->m_Parent = this;
}