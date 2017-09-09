// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "GM.h"

#include "SFML/Graphics.hpp"

class GMRoom :
	public GMResource
{
public:
	GMRoom(GMProject2* Project, std::string Key, std::string DataPath);
};