// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once
#include "Room/Layer.h"
#include <memory>

class GMRInstance;

class GMRInstanceLayer : public GMRLayer
{
private:
	std::vector<std::shared_ptr<GMRInstance>> m_Instances;

private:
	void SetDefaults(GMRoom* Room);

public:
	GMRInstanceLayer(GMRoom* Room); // default constructor
	GMRInstanceLayer(GMRoom* Room, rapidjson::Value& Stored); // loaded room constructor

	virtual rapidjson::Document GetJSON() const;
	virtual void Draw(sf::RenderTarget& Target) const;

	GMRInstance* GetInstance(unsigned Index) const;
	GMRInstance* GetInstanceByKey(std::string Key) const;
	GMRInstance* GetInstanceByName(std::string Name) const;
	unsigned GetNumInstances() const { return m_Instances.size(); }
};
