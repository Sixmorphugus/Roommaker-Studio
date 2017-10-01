// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"
#include <SFML/Graphics.hpp>

class GMProject2;

// GMS Definitions/Defaults
#define EMPTY_GUID "00000000-0000-0000-0000-000000000000"

/*
 GMResourceType
 Enum list of all useful GameMaker resource types.
 */
enum GMResourceType
{
	Ignored,
	Sprite,
	Folder,
	Object,
	Room,
	TileSet
};

/*
 GMResource
 Base class for a GameMaker resource.
 */
class RMSDLL GMResource
{
private:
	std::string m_Key;
	std::string m_DataPath;
	std::string m_Name;

	GMProject2* m_Project;

	class GMResourceContainer* m_Parent;

	GMResourceType m_SaveType;

public:
	GMResource(GMProject2* Project, std::string Key, std::string DataPath);

	std::string GetKey() const { return m_Key; }
	std::string GetDataPath() const { return m_DataPath; }
	std::string GetName() const { return m_Name; }
	GMProject2* GetProject() const; // Just to be safe, this isn't inline.
	GMResourceContainer* GetParent() const; // Same as above
	virtual GMResourceType GetType() const { return Ignored; }
	virtual GMResourceType GetFilterType() const { return GetType(); }
	virtual void Init() {}

	std::string GetRealPath() const;

	void SetName(std::string Name) { m_Name = Name; }

	GMResourceType GetSaveType() { return m_SaveType; }
	void SetSaveType(GMResourceType SaveType) { m_SaveType = SaveType; }

	friend GMResourceContainer;
};

/*
 GMResourceContainer
 Standardized GMResourceContainer.
 
 ONE REQUIREMENT: When you add things to your containment, CALL PARENT.
 */
class RMSDLL GMResourceContainer
{
private:
	GMProject2* m_Project;

public:
	GMResourceContainer(GMProject2* Project);

	virtual unsigned GetNumResources() const = 0;
	virtual GMResource* GetResource(unsigned i) const = 0;
	virtual GMResource* GetResourceByName(std::string Name);

	// Helper for finding if a folder contains something.
	bool HasChild(GMResource* Memory) const;
	bool HasChild(std::string Key) const;

protected:
	virtual void Parent(GMResource* Memory);

	virtual unsigned GetNumAllResources() const;
	virtual GMResource* GetAllResource(unsigned i) const;
};

sf::Color DecompressColor(unsigned Color);
unsigned CompressColor(sf::Color Color);
std::string GenerateGUID(bool empty = false);

bool RegisterTakenGUID(std::string NewGUID);
void PurgeTakenGUIDs();