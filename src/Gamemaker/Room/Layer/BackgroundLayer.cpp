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

GMRBackgroundLayer::GMRBackgroundLayer(GMRoom* Room, rapidjson::GenericObject<false, rapidjson::GenericValue<rapidjson::UTF8<>>>& Stored)
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
	m_HSpeed = Stored["vspeed"].GetFloat();

	assert(Stored["htiled"].IsBool());
	m_HSpeed = Stored["htiled"].GetBool();

	assert(Stored["vtiled"].IsBool());
	m_HSpeed = Stored["vtiled"].GetBool();

	assert(Stored["stretch"].IsBool());
	m_HSpeed = Stored["stretch"].GetBool();

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

void GMRBackgroundLayer::Draw(sf::RenderTarget& Target)
{
	//Target.clear(m_Color);

	sf::RectangleShape outRect;

	outRect.setPosition(0, 0);
	outRect.setSize(sf::Vector2f(GetRoom()->GetWidth(), GetRoom()->GetHeight()));
	outRect.setFillColor(m_Color);

	Target.draw(outRect);
}

rapidjson::Document GMRBackgroundLayer::GetJSON()
{
	rapidjson::Document Stored = GMRLayer::GetJSON();

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