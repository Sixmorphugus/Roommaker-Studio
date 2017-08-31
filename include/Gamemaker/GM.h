// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"

class GMProject2;

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

public:
	GMResource(GMProject2* Project, std::string Key, std::string DataPath);

	std::string GetKey() { return m_Key; }
	std::string GetDataPath() { return m_DataPath; }
	std::string GetName() { return m_Name; }
	GMProject2* GetProject(); // Just to be safe, this isn't inline.
	GMResourceContainer* GetParent(); // Same as above
	virtual GMResourceType GetType() { return Ignored; }
	virtual GMResourceType GetFilterType() { return GetType(); }
	virtual void Init() {}

	std::string GetRealPath();

	void SetName(std::string Name) { m_Name = Name; }

	friend GMResourceContainer;
};

/*
 GMResourceContainer
 Standardized GMResourceContainer.
 
 ONE REQUIREMENT: When you add things to your containment, CALL PARENT.
 */
class RMSDLL GMResourceContainer
{
public:
	GMResourceContainer() {}

	virtual unsigned GetNumResources() = 0;
	virtual GMResource* GetResource(unsigned i) = 0;

	// Helper for finding if a folder contains something.
	bool HasChild(GMResource* Memory);
	bool HasChild(std::string Key);

protected:
	virtual void Parent(GMResource* Memory);
};
