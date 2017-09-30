// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once
#include "Room/Layer.h"

class GMRInstanceLayer : public GMRLayer
{
private:
	

private:
	void SetDefaults(GMRoom* Room);

public:
	GMRInstanceLayer(GMRoom* Room); // default constructor
	GMRInstanceLayer(GMRoom* Room, rapidjson::GenericObject<false, rapidjson::GenericValue<rapidjson::UTF8<>>>& Stored); // loaded room constructor

	virtual rapidjson::Document GetJSON();
	virtual void Draw(sf::RenderTarget& Target);
};
