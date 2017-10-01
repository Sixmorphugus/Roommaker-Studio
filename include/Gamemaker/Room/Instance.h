// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"
#include "rapidjson/document.h"
#include "SFML/Graphics.hpp"

class GMObject;
class GMRInstanceLayer;

class RMSDLL GMRInstance
{
private:
	std::string m_Key;

	bool m_Ignore;
	bool m_InheritItemSettings;
	bool m_serialiseFrozen; // (sic)
	bool m_IsDnD;
	bool m_InheritCreationCode;

	float m_X;
	float m_Y;
	float m_Rotation;
	float m_ScaleX;
	float m_ScaleY;
	
	std::string m_Name;
	std::string m_NameWithNoFileRename;
	
	sf::Color m_Color;
	
	std::string m_CreationCode;
	
	GMObject* m_OriginalParent;
	GMObject* m_Object;
	GMRInstanceLayer* m_InstLayer;

private:
	void SetDefaults(GMRInstanceLayer* InstanceLayer);
	std::string GenerateInstanceName();

public:
	// Create a new instance
	GMRInstance(class GMRInstanceLayer* InstanceLayer, GMObject* Type);

	// Load an existing one
	GMRInstance(class GMRInstanceLayer* InstanceLayer, rapidjson::Value& Stored);

	rapidjson::Document GetJSON() const;
	void Draw(sf::RenderTarget& Target) const;

	GMRInstanceLayer* GetInstanceLayer() const { return m_InstLayer; }

	std::string GetKey() const { return m_Key; }

	bool GetIsIgnored() const { return m_Ignore; }
	void SetIsIgnored(bool Ignore) { m_Ignore = Ignore; }

	GMObject* GetObject() const { return m_Object; }
	void SetObject(GMObject* Object) { assert(Object); m_Object = Object; }

	bool GetInheritsItemSettings() const { return m_InheritItemSettings; }
	void SetInheritsItemSettings(bool val) { m_InheritItemSettings = val; }

	bool GetSerialiseFrozen() const { return m_serialiseFrozen; }
	void SetSerialiseFrozen(bool val) { m_serialiseFrozen = val; }

	bool GetIsDnD() const { return m_IsDnD; }
	void SetIsDnD(bool val) { m_IsDnD = val; }

	bool GetInheritsCreationCode() const { return m_InheritCreationCode; }
	void SetInheritsCreationCode(bool val) { m_InheritCreationCode = val; }

	float GetPositionX() const { return m_X; }
	void SetPositionX(float val) { m_X = val; }
	float GetPositionY() const { return m_Y; }
	void SetPositionY(float val) { m_Y = val; }
	void SetPosition(float X, float Y) { SetPositionX(X); SetPositionY(Y); }

	float GetRotation() const { return m_Rotation; }
	void SetRotation(float val) { m_Rotation = val; }

	float GetScaleX() const { return m_ScaleX; }
	void SetScaleX(float val) { m_ScaleX = val; }
	float GetScaleY() const { return m_ScaleY; }
	void SetScaleY(float val) { m_ScaleY = val; }
	void SetScale(float X, float Y) { SetScaleX(X); SetScaleY(Y); }

	std::string GetName() const { return m_Name; }
	void SetName(std::string Name) { m_Name = Name; m_NameWithNoFileRename = Name; }

	sf::Color GetColor() const { return m_Color; }
	void SetColor(sf::Color val) { m_Color = val; }

	std::string GetCreationCode() const { return m_CreationCode; }
	void SetCreationCode(std::string val) { m_CreationCode = val; }
};