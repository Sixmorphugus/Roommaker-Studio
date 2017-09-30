// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "GM.h"
#include "Project2.h"
#include <random>
#include <unordered_set>

using namespace std;

GMResource::GMResource(GMProject2* Project, string Key, string DataPath)
{
	m_Key = Key;
	m_DataPath = DataPath;
	m_Project = Project;
	m_Parent = Project;
	m_Name = "N/A";

	// not entirely sure how GMS's GUID system works or where it allows duplicates so we don't care if this fails
	RegisterTakenGUID(Key);
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


GMResourceContainer::GMResourceContainer(GMProject2* Project)
{
	m_Project = Project;
}

GMResource* GMResourceContainer::GetResourceByName(std::string Name)
{
	for (unsigned i = 0; i < GetNumResources(); i++)
	{
		if (GetResource(i)->GetName() == Name)
			return GetResource(i);
	}

	RMS_LogWarn("Resource not found: " + Name);

	return NULL;
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

unsigned GMResourceContainer::GetNumAllResources()
{
	return m_Project->m_Resources.size();
}

GMResource* GMResourceContainer::GetAllResource(unsigned i)
{
	if (i >= GetNumAllResources())
		return NULL;

	return m_Project->m_Resources[i].get();
}

sf::Color DecompressColor(unsigned Color)
{
	unsigned B = (Color & 0x000000FF);
	unsigned G = (Color & 0x0000FF00) >> 8;
	unsigned R = (Color & 0x00FF0000) >> 16;
	unsigned A = (Color & 0xFF000000) >> 24;

	return sf::Color(R, G, B, A);
}

unsigned CompressColor(sf::Color Color)
{
	unsigned Col = Color.b;

	Col |= ((unsigned)Color.g << 8);
	Col |= ((unsigned)Color.r << 16);
	Col |= ((unsigned)Color.a << 24);

	return Col;
}

std::string GenerateGUID(bool empty /*= false*/)
{
	string GUID = EMPTY_GUID;

	if (empty)
	{
		return GUID;
	}

	// random character for every 0
	while (!RegisterTakenGUID(GUID)) {
		for (unsigned i = 0; i < GUID.size(); i++)
		{
			if (GUID[i] == '0')
			{
				GUID[i] = (char)((rand() % 127 - 33) + 33);
			}
		}
	}

	return GUID;
}

static unordered_set<string> TakenGUIDs;

bool RegisterTakenGUID(std::string NewGUID)
{
	if (NewGUID == EMPTY_GUID) return false; // failure; never accept the EMPTY_GUID

	if (TakenGUIDs.find(NewGUID) == TakenGUIDs.end()) { // not a GUID already
		TakenGUIDs.insert(NewGUID);
		return true; // success
	}
	else return false; // failure, GUID exists
}

void PurgeTakenGUIDs()
{
	TakenGUIDs.clear();
}

