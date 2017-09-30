// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once
#include "Room/Layer.h"

class GMRBackgroundLayer : public GMRLayer
{
private:
	int m_AnimationFps;
	bool m_AnimationFpsIsUserDefined;
	unsigned m_AnimationSpeedType;
	sf::Color m_Color;

	int m_HSpeed;
	int m_VSpeed;

	bool m_HTiled;
	bool m_VTiled;
	bool m_Stretch;

	int m_X;
	int m_Y;

	class GMSprite* m_Sprite;

private:
	void SetDefaults(GMRoom* Room);

public:
	GMRBackgroundLayer(GMRoom* Room); // default constructor
	GMRBackgroundLayer(GMRoom* Room, rapidjson::GenericObject<false, rapidjson::GenericValue<rapidjson::UTF8<>>>& Stored); // loaded room constructor

	virtual rapidjson::Document GetJSON();
	virtual void Draw(sf::RenderTarget& Target);

	// Animation FPS
	int GetAnimationFPS() { return m_AnimationFps; }
	void SetAnimationFPS(int AnimationFPS) { m_AnimationFps = AnimationFPS; }

	bool GetAnimationFPSIsUserDefined() { return m_AnimationFpsIsUserDefined; }
	void SetAnimationFPSIsUserDefined(bool AnimationFPSIsUserDefined) { m_AnimationFpsIsUserDefined = AnimationFPSIsUserDefined; }

	// Animation speed type (?)
	unsigned GetAnimationSpeedType() { return m_AnimationSpeedType; }
	void SetAnimationSpeedType(unsigned AnimationSpeedType) { m_AnimationSpeedType = AnimationSpeedType; }

	// Color
	sf::Color GetBackgroundColor() { return m_Color; }
	void SetBackgroundColor(sf::Color Color) { m_Color = Color; }

	// Animation
	int GetBackgroundHSpeed() { return m_HSpeed; }
	void SetBackgroundHSpeed(int HSpeed) { m_HSpeed = HSpeed; }
	int GetBackgroundVSpeed() { return m_VSpeed; }
	void SetBackgroundVSpeed(int VSpeed) { m_VSpeed = VSpeed; }

	void SetBackgroundSpeed(int HSpeed, int VSpeed) { SetBackgroundHSpeed(HSpeed); SetBackgroundVSpeed(VSpeed); }

	// Background position
	int GetBackgroundXPosition() { return m_X; }
	void SetBackgroundXPosition(int X) { m_X = X; }
	int GetBackgroundYPosition() { return m_Y; }
	void SetBackgroundYPosition(int Y) { m_Y = Y; }

	void SetBackgroundPosition(int X, int Y) { SetBackgroundXPosition(X); SetBackgroundYPosition(Y); }

	// Sprite
	GMSprite* GetSprite() { return m_Sprite; }
	void SetSprite(GMSprite* Sprite) { m_Sprite = Sprite; }
};
