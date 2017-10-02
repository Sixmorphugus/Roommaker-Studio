// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Room/Layer/BackgroundLayer.h"
#include "Sprite.h"
#include "Room.h"
#include "Project2.h"

void GMRBackgroundLayer::SetDefaults(GMRoom* Room)
{
	m_AnimationFps = 15;
	m_AnimationSpeedType = 0;
	m_Color = sf::Color::Black;
	m_HSpeed = 0;
	m_VSpeed = 0;

	m_HTiled = false;
	m_VTiled = false;
	m_Stretch = false;
	
	m_Sprite = NULL;
			
	m_AnimationFpsIsUserDefined = false;

	m_X = 0;
	m_Y = 0;
}

GMRBackgroundLayer::GMRBackgroundLayer(GMRoom* Room, rapidjson::Value& Stored)
	: GMRLayer(Room, Stored)
{
	SetDefaults(Room);

	// Load background information from JSON
	assert(Stored["animationFPS"].IsInt());
	m_AnimationFps = Stored["animationFPS"].GetInt();

	assert(Stored["animationSpeedType"].IsInt() || Stored["animationSpeedType"].IsString());

	if (Stored["animationSpeedType"].IsInt())
		m_AnimationSpeedType = Stored["animationSpeedType"].GetInt();
	else
		m_AnimationSpeedType = atoi(Stored["animationSpeedType"].GetString());

	assert(Stored["colour"].IsObject());
	assert(Stored["colour"]["Value"].IsUint());
	m_Color = DecompressColor(Stored["colour"]["Value"].GetUint());

	assert(Stored["hspeed"].IsNumber());
	m_HSpeed = Stored["hspeed"].GetFloat();

	assert(Stored["vspeed"].IsNumber());
	m_VSpeed = Stored["vspeed"].GetFloat();

	assert(Stored["htiled"].IsBool());
	m_HTiled = Stored["htiled"].GetBool();

	assert(Stored["vtiled"].IsBool());
	m_VTiled = Stored["vtiled"].GetBool();

	assert(Stored["stretch"].IsBool());
	m_Stretch = Stored["stretch"].GetBool();

	assert(Stored["userdefined_animFPS"].IsBool());
	m_AnimationFpsIsUserDefined = Stored["userdefined_animFPS"].GetBool();

	assert(Stored["spriteId"].IsString());
	auto rc = GetRoom()->GetProject()->FindResource(Stored["spriteId"].GetString());
	m_Sprite = dynamic_cast<GMSprite*>(rc);

	assert(Stored["x"].IsNumber());
	m_X = Stored["x"].GetFloat();

	assert(Stored["y"].IsNumber());
	m_Y = Stored["y"].GetFloat();
}

GMRBackgroundLayer::GMRBackgroundLayer(GMRoom* Room)
	: GMRLayer(Room)
{
	SetDefaults(Room);
}

void GMRBackgroundLayer::Draw(sf::RenderTarget& Target) const
{
	if (m_Sprite)
	{
		// sprite based background
		sf::Sprite sfmlSprite = m_Sprite->ToSfSprite();
		sf::Texture* sfmlTexture = m_Sprite->GetFrame0Texture();

		sfmlSprite.setOrigin(0, 0);
		sfmlSprite.setColor(m_Color);
		sfmlSprite.setPosition(0, 0);

		if (m_Stretch)
		{
			sfmlSprite.setScale(GetRoom()->GetWidth() / sfmlTexture->getSize().x, GetRoom()->GetHeight() / sfmlTexture->getSize().y);
		}
		else {
			if (m_HTiled)
			{
				//sfmlSprite.setScale(1.f, sfmlSprite.getScale().y);
				sfmlSprite.setTextureRect(sf::IntRect(0, 0, GetRoom()->GetWidth(), sfmlSprite.getTextureRect().height));
			}

			if (m_VTiled)
			{
				//sfmlSprite.setScale(sfmlSprite.getScale().x, 1.f);
				sfmlSprite.setTextureRect(sf::IntRect(0, 0, sfmlSprite.getTextureRect().width, GetRoom()->GetHeight()));
			}
		}

		Target.draw(sfmlSprite);
	}
	else
	{
		// solid color background
		sf::RectangleShape outRect;

		outRect.setPosition(0, 0);
		outRect.setSize(sf::Vector2f(GetRoom()->GetWidth(), GetRoom()->GetHeight()));
		outRect.setFillColor(m_Color);

		Target.draw(outRect);
	}

	GMRLayer::Draw(Target);
}

rapidjson::Document GMRBackgroundLayer::GetJSON()
{
	rapidjson::Document Stored = GMRLayer::GetJSON();

	Stored["__type"] = "GMRBackgroundLayer_Model:#YoYoStudio.MVCFormat";
	Stored["modelName"] = "GMRInstanceLayer";

	Stored["animationFPS"] = m_AnimationFps;
	Stored["animationSpeedType"] = m_AnimationSpeedType;

	Stored["colour"]["Value"] = CompressColor(m_Color);

	Stored["hspeed"] = m_HSpeed;
	Stored["vspeed"] = m_VSpeed;

	Stored["htiled"] = m_HTiled;
	Stored["vtiled"] = m_VTiled;

	Stored["stretch"] = m_Stretch;

	Stored["userdefined_animFPS"] = m_AnimationFpsIsUserDefined;

	if (m_Sprite)
	{
		Stored["spriteId"].SetString(m_Sprite->GetKey().c_str(), m_Sprite->GetKey().size());
	}
	else
	{
		auto guid = GenerateGUID(true);
		Stored["spriteId"].SetString(guid.c_str(), guid.size());
	}

	Stored["x"] = m_X;
	Stored["y"] = m_Y;

	return Stored;
}
