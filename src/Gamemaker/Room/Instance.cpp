// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "Room/Instance.h"
#include "Room/Layer/InstanceLayer.h"
#include "Room.h"
#include "Project2.h"
#include "Object.h"
#include "Sprite.h"

#define EMPTY_INST "inst_00000000"

using namespace std;

void GMRInstance::SetDefaults(class GMRInstanceLayer* InstanceLayer)
{
	m_InstLayer = InstanceLayer;

	m_Key = GenerateGUID();

	m_Ignore = false;
	SetInheritsItemSettings(false);
	SetSerialiseFrozen(false);
	SetIsDnD(false);
	SetInheritsCreationCode(false);

	SetPositionX(0.f);
	SetPositionY(0.f);
	SetRotation(0.f);
	SetScaleX(1.f);
	SetScaleY(1.f);

	m_Name = GenerateInstanceName();
	m_NameWithNoFileRename = m_Name;

	SetColor(sf::Color::White);

	SetCreationCode("");

	m_OriginalParent = NULL;
	m_Object = NULL;
}

string GMRInstance::GenerateInstanceName()
{
	string StarterName = EMPTY_INST;

	// random character for every 0
	for (unsigned i = 0; i < StarterName.size(); i++)
	{
		if (StarterName[i] == '0')
		{
			StarterName[i] = toupper((char)((rand() % 127 - 33) + 33));
		}
	}

	return StarterName;
}

GMRInstance::GMRInstance(class GMRInstanceLayer* InstanceLayer, class GMObject* Type)
{
	SetDefaults(InstanceLayer);
	SetObject(Type);
}

GMRInstance::GMRInstance(class GMRInstanceLayer* InstanceLayer, rapidjson::Value& Stored)
{
	SetDefaults(InstanceLayer);

	// Load existing instance information
	assert(Stored["id"].IsString());
	m_Key = Stored["id"].GetString();

	assert(Stored["colour"].IsObject());
	assert(Stored["colour"]["Value"].IsUint());
	m_Color = DecompressColor(Stored["colour"]["Value"].GetUint());

	assert(Stored["ignore"].IsBool());
	m_Ignore = Stored["ignore"].GetBool();

	assert(Stored["inheritItemSettings"].IsBool());
	m_InheritItemSettings = Stored["inheritItemSettings"].GetBool();

	assert(Stored["m_serialiseFrozen"].IsBool());
	m_serialiseFrozen = Stored["m_serialiseFrozen"].GetBool();

	assert(Stored["IsDnD"].IsBool());
	m_IsDnD = Stored["IsDnD"].GetBool();

	assert(Stored["inheritCode"].IsBool());
	m_InheritCreationCode = Stored["inheritCode"].GetBool();

	assert(Stored["x"].IsNumber());
	m_X = Stored["x"].GetFloat();

	assert(Stored["y"].IsNumber());
	m_Y = Stored["y"].GetFloat();

	assert(Stored["scaleX"].IsNumber());
	m_ScaleX = Stored["scaleX"].GetFloat();

	assert(Stored["scaleY"].IsNumber());
	m_ScaleY = Stored["scaleY"].GetFloat();

	assert(Stored["rotation"].IsNumber());
	m_Rotation = Stored["rotation"].GetFloat();

	assert(Stored["name"].IsString());
	m_Name = Stored["name"].GetString();

	assert(Stored["name_with_no_file_rename"].IsString());
	m_NameWithNoFileRename = Stored["name_with_no_file_rename"].GetString();

	assert(Stored["objId"].IsString());
	GMResource* FoundResource = m_InstLayer->GetRoom()->GetProject()->FindResource(Stored["objId"].GetString());
	m_Object = dynamic_cast<GMObject*>(FoundResource);

	assert(Stored["m_originalParentID"].IsString());
	m_OriginalParent = dynamic_cast<GMObject*>(m_InstLayer->GetRoom()->GetProject()->FindResource(Stored["m_originalParentID"].GetString()));

	if (Stored["creationCodeFile"].IsString());
	string CodeFileName = Stored["creationCodeFile"].GetString();

	RMSPlatform::LoadTextFile(m_CreationCode, RMSPlatform::Dir(m_InstLayer->GetRoom()->GetRealPath()) + "/" + CodeFileName);
}

rapidjson::Document GMRInstance::GetJSON() const
{
	rapidjson::Document Stored;

	// write assumed vars first
	Stored["modelName"] = "GMRInstance";
	Stored["mvc"] = "1.0";

	// Write Data
	Stored["id"].SetString(m_Key.c_str(), m_Key.size());

	Stored["colour"]["Value"] = CompressColor(m_Color);

	Stored["ignore"] = m_Ignore;
	Stored["inheritItemSettings"] = m_InheritItemSettings;
	Stored["m_serialiseFrozen"] = m_serialiseFrozen;
	Stored["IsDnD"] = m_IsDnD;
	Stored["inheritCode"] = m_InheritCreationCode;

	Stored["x"] = m_X;
	Stored["y"] = m_Y;
	Stored["scaleX"] = m_ScaleX;
	Stored["scaleY"] = m_ScaleY;
	Stored["rotation"] = m_Rotation;

	Stored["name"].SetString(m_Name.c_str(), m_Name.size());
	Stored["name_with_no_file_rename"].SetString(m_NameWithNoFileRename.c_str(), m_NameWithNoFileRename.size());

	if (m_Object)
	{
		Stored["objId"].SetString(m_Object->GetKey().c_str(), m_Object->GetKey().size());
	}
	else
	{
		string GUID = GenerateGUID(true);
		Stored["objId"].SetString(GUID.c_str(), GUID.size());
	}

	if (m_OriginalParent)
	{
		Stored["m_originalParentID"].SetString(m_OriginalParent->GetKey().c_str(), m_OriginalParent->GetKey().size());
	}
	else
	{
		string GUID = GenerateGUID(true);
		Stored["m_originalParentID"].SetString(GUID.c_str(), GUID.size());
	}

	// Save creation code file if there's any
	if (m_CreationCode != "")
	{
		string Filename = "InstanceCreationCode_" + GetName() + ".gml";
		Stored["creationCodeFile"].SetString(Filename.c_str(), Filename.size());
		RMSPlatform::SaveTextFile(m_CreationCode, RMSPlatform::Dir(m_InstLayer->GetRoom()->GetRealPath()) + "/" + Filename);
	}
	else
	{
		Stored["creationCodeFile"] = "";
	}

	return Stored;
}

void GMRInstance::Draw(sf::RenderTarget& Target) const
{
	// Draw the instance wherever it is at the requested position, rotation and scale
	GMSprite* ObjSprite = m_Object->GetSprite();

	sf::Sprite sprToDraw = GMSprite::GetDefaultSfSprite();

	if (ObjSprite)
	{
		sprToDraw = ObjSprite->ToSfSprite();
	}

	sprToDraw.setPosition(m_X, m_Y);
	sprToDraw.setRotation(m_Rotation);
	sprToDraw.setScale(m_ScaleX, m_ScaleY);

	Target.draw(sprToDraw);
}
