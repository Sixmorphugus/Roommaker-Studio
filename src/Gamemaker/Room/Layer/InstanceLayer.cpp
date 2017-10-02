// Copyright Chris Sixsmith 2017. All Rights Reserved.
#include "Room/Layer/InstanceLayer.h"
#include "Room/Instance.h"

void GMRInstanceLayer::SetDefaults(GMRoom* Room)
{
	// ...
}

GMRInstanceLayer::GMRInstanceLayer(GMRoom* Room)
	: GMRLayer(Room)
{
	SetDefaults(Room);
}

GMRInstanceLayer::GMRInstanceLayer(GMRoom* Room, rapidjson::Value& Stored)
	: GMRLayer(Room)
{
	SetDefaults(Room);

	// load instances
	assert(Stored["instances"].IsArray());
	auto StoredInstanceArray = Stored["instances"].GetArray();

	for (auto& StoredInstance : StoredInstanceArray)
	{
		assert(StoredInstance.IsObject());
		m_Instances.push_back(std::make_shared<GMRInstance>(this, StoredInstance));
	}
}

rapidjson::Document GMRInstanceLayer::GetJSON() const
{
	rapidjson::Document Stored = GMRLayer::GetJSON();

	// save instances
	Stored["modelName"] = "GMRInstanceLayer";
	Stored["__type"] = "GMRInstanceLayer_Model:#YoYoStudio.MVCFormat";

	Stored["instances"].SetArray();
	auto Array = Stored["instances"].GetArray();

	rapidjson::Document::AllocatorType& allocator = Stored.GetAllocator();

	for (auto& Inst : m_Instances)
	{
		auto ObjJson = Inst->GetJSON().GetObject();
		Array.PushBack(ObjJson, allocator);
	}

	return Stored;
}

void GMRInstanceLayer::Draw(sf::RenderTarget& Target) const
{
	// Draw all instances
	for (auto& Inst : m_Instances)
	{
		Inst->Draw(Target);
	}

	GMRLayer::Draw(Target);
}

GMRInstance* GMRInstanceLayer::GetInstance(unsigned Index) const
{
	if (Index >= GetNumInstances())
	{
		return NULL;
	}

	return m_Instances[Index].get();
}

GMRInstance* GMRInstanceLayer::GetInstanceByKey(std::string Key) const
{
	for (auto& Inst : m_Instances)
	{
		if (Inst->GetKey() == Key)
		{
			return Inst.get();
		}
	}

	return NULL;
}

GMRInstance* GMRInstanceLayer::GetInstanceByName(std::string Name) const
{
	for (auto& Inst : m_Instances)
	{
		if (Inst->GetName() == Name)
		{
			return Inst.get();
		}
	}

	return NULL;
}
