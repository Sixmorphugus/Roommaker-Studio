// Copyright Chris Sixsmith 2017. All Rights Reserved.
#include "Room/Layer/InstanceLayer.h"

void GMRInstanceLayer::SetDefaults(GMRoom* Room)
{
	// ...
}

GMRInstanceLayer::GMRInstanceLayer(GMRoom* Room)
	: GMRLayer(Room)
{
	SetDefaults(Room);
}

GMRInstanceLayer::GMRInstanceLayer(GMRoom* Room, rapidjson::GenericObject<false, rapidjson::GenericValue<rapidjson::UTF8<>>>& Stored)
	: GMRLayer(Room)
{
	SetDefaults(Room);

	// load instances
	// ...
}

rapidjson::Document GMRInstanceLayer::GetJSON()
{
	rapidjson::Document Stored = GMRLayer::GetJSON();

	// save instances
	// ...

	return Stored;
}

void GMRInstanceLayer::Draw(sf::RenderTarget& Target)
{
	// Draw all instances
	// ...
}

