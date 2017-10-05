// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once
#include "Room/Layer.h"
#include <memory>

class GMRGraphic;

class GMRAssetLayer : public GMRLayer
{
private:
	std::vector<std::shared_ptr<GMRGraphic>> m_Assets;

private:
	void SetDefaults(GMRoom* Room);

public:
	GMRAssetLayer(GMRoom* Room); // default constructor
	GMRAssetLayer(GMRoom* Room, rapidjson::Value& Stored); // loaded room constructor

	virtual rapidjson::Document GetJSON() const;
	virtual void Draw(sf::RenderTarget& Target) const;

	GMRGraphic* GetGraphic(unsigned Index) const;
	GMRGraphic* GetGraphicByKey(std::string Key) const;
	GMRGraphic* GetGraphicByName(std::string Name) const;
	unsigned GetNumGraphics() const { return m_Assets.size(); }
};
