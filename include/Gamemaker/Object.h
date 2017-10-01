// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "GM.h"

class GMObject :
	public GMResource
{
private:
	class GMSprite* m_Sprite;

public:
	GMObject(GMProject2* Project, std::string Key, std::string DataPath);

	virtual void Init();
	GMSprite* GetSprite() const { return m_Sprite; }
};