// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "GM.h"

#include "SFML/Graphics.hpp"

class GMSprite :
	public GMResource
{
private:
	sf::Texture m_Frame0;
	sf::Sprite m_SpriteSetup;

public:
	GMSprite(GMProject2* Project, std::string Key, std::string DataPath);

	sf::Texture* GetFrame0Texture() { return &m_Frame0; }
	sf::Sprite ToSfSprite() const { return m_SpriteSetup; }

	static sf::Sprite GetDefaultSfSprite();
};