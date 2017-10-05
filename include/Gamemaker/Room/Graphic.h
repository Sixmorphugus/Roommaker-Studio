// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"
#include "rapidjson/document.h"
#include "SFML/Graphics.hpp"

class GMSprite;
class GMRAssetLayer;

class RMSDLL GMRGraphic
{
private:
	std::string m_Key;

	bool m_Ignore;
	bool m_InheritItemSettings;
	bool m_serialiseFrozen; // (sic)

	float m_X;
	float m_Y;
	float m_Rotation;
	float m_ScaleX;
	float m_ScaleY;

	int m_AnimationFPS;
	unsigned m_AnimationSpeedType;
	unsigned m_FrameIndex;
	bool m_UserDefinedAnimFPS;

	std::string m_Name;
	std::string m_NameWithNoFileRename;

	sf::Color m_Color;

	GMSprite* m_OriginalParent;
	GMSprite* m_Sprite;
	GMRAssetLayer* m_AssetLayer;

private:
	void SetDefaults(GMRAssetLayer* GraphicLayer);
	std::string GenerateGraphicName();

public:
	// Create a new instance
	GMRGraphic(class GMRAssetLayer* GraphicLayer, GMSprite* Type);

	// Load an existing one
	GMRGraphic(class GMRAssetLayer* GraphicLayer, rapidjson::Value& Stored);

	rapidjson::Document GetJSON() const;
	void Draw(sf::RenderTarget& Target) const;

	GMRAssetLayer* GetGraphicLayer() const { return m_AssetLayer; }

	std::string GetKey() const { return m_Key; }

	bool GetIsIgnored() const { return m_Ignore; }
	void SetIsIgnored(bool Ignore) { m_Ignore = Ignore; }

	GMSprite* GetSprite() const { return m_Sprite; }
	void SetSprite(GMSprite* Sprite) { assert(Sprite); m_Sprite = Sprite; }

	bool GetInheritsItemSettings() const { return m_InheritItemSettings; }
	void SetInheritsItemSettings(bool val) { m_InheritItemSettings = val; }

	bool GetSerialiseFrozen() const { return m_serialiseFrozen; }
	void SetSerialiseFrozen(bool val) { m_serialiseFrozen = val; }

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

	int GetAnimationFPS() const { return m_AnimationFPS; }
	void SetAnimationFPS(int val) { m_AnimationFPS = val; }

	unsigned GetAnimationSpeedType() const { return m_AnimationSpeedType; }

	unsigned GetFrameIndex() const { return m_FrameIndex; }
	void SetFrameIndex(unsigned val) { m_FrameIndex = val; }

	bool GetHasUserDefinedAnimFPS() const { return m_UserDefinedAnimFPS; }
	void SetHasUserDefinedAnimFPS(bool val) { m_UserDefinedAnimFPS = val; }
};