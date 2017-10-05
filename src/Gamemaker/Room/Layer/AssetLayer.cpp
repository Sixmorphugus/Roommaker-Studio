// Copyright Chris Sixsmith 2017. All Rights Reserved.
#include "Room/Layer/AssetLayer.h"
#include "Room/Graphic.h"

void GMRAssetLayer::SetDefaults(GMRoom* Room)
{
	// ...
}

GMRAssetLayer::GMRAssetLayer(GMRoom* Room)
	: GMRLayer(Room)
{
	SetDefaults(Room);
}

GMRAssetLayer::GMRAssetLayer(GMRoom* Room, rapidjson::Value& Stored)
	: GMRLayer(Room)
{
	SetDefaults(Room);

	// load instances
	assert(Stored["assets"].IsArray());
	auto StoredAssetArray = Stored["assets"].GetArray();

	for (auto& StoredAsset : StoredAssetArray)
	{
		assert(StoredAsset.IsObject());
		m_Assets.push_back(std::make_shared<GMRGraphic>(this, StoredAsset));
	}
}

rapidjson::Document GMRAssetLayer::GetJSON() const
{
	rapidjson::Document Stored = GMRLayer::GetJSON();

	// save instances
	Stored["modelName"] = "GMRAssetLayer";
	Stored["__type"] = "GMRAssetLayer_Model:#YoYoStudio.MVCFormat";

	Stored["assets"].SetArray();
	auto Array = Stored["assets"].GetArray();

	rapidjson::Document::AllocatorType& allocator = Stored.GetAllocator();

	for (auto& Inst : m_Assets)
	{
		auto ObjJson = Inst->GetJSON().GetObject();
		Array.PushBack(ObjJson, allocator);
	}

	return Stored;
}

void GMRAssetLayer::Draw(sf::RenderTarget& Target) const
{
	// Draw all instances
	for (auto& Inst : m_Assets)
	{
		Inst->Draw(Target);
	}

	GMRLayer::Draw(Target);
}

GMRGraphic* GMRAssetLayer::GetGraphic(unsigned Index) const
{
	if (Index >= GetNumGraphics())
	{
		return NULL;
	}

	return m_Assets[Index].get();
}

GMRGraphic* GMRAssetLayer::GetGraphicByKey(std::string Key) const
{
	for (auto& Inst : m_Assets)
	{
		if (Inst->GetKey() == Key)
		{
			return Inst.get();
		}
	}

	return NULL;
}

GMRGraphic* GMRAssetLayer::GetGraphicByName(std::string Name) const
{
	for (auto& Inst : m_Assets)
	{
		if (Inst->GetName() == Name)
		{
			return Inst.get();
		}
	}

	return NULL;
}
