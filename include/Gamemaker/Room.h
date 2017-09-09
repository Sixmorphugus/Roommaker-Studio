// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "GM.h"

#include "SFML/Graphics.hpp"

class GMRoom :
	public GMResource
{
private:
	// Room Content
	std::string m_CreationCode;
	GMRoom* m_ParentRoom;
	//std::vector<GMLayer> m_Layers;
	//GMView m_Views[8];

	// Physics settings
	bool m_isPhysicsWorld;
	float m_PhysicsWorldGravityX;
	float m_PhysicsWorldGravityY;
	float m_PhysicsWorldPixToMeters;
	bool m_PhysicsWorldInheritSettings;

	// Room Settings
	int m_Width;
	int m_Height;
	bool m_Persistent;
	bool m_InheritSettings;

	// View Settings
	bool m_EnableViews;
	bool m_ViewsClearDisplayBuffer;
	bool m_ViewsClearBackground;
	bool m_ViewsInheritSettings;

public:
	//GMRoom(GMProject2* Project); // Create a new room
	GMRoom(GMProject2* Project, std::string Key, std::string DataPath); // Load an existing room

	// Room stuff
	GMRoom* GetParentRoom() { return m_ParentRoom; }
	void SetParentRoom(GMRoom* ParentRoom) { m_ParentRoom = ParentRoom; }

	std::string GetCreationCode() { return m_CreationCode; }
	void SetCreationCode(std::string CreationCode) { m_CreationCode = CreationCode; }

	// Manipulate physics settings
	bool GetIsPhysicsWorld() { return m_isPhysicsWorld; }
	void SetIsPhysicsWorld(bool IsPhysicsWorld) { m_isPhysicsWorld = IsPhysicsWorld; }

	float GetPhysicsWorldGravityX() { return m_PhysicsWorldGravityX; }
	float GetPhysicsWorldGravityY() { return m_PhysicsWorldGravityY; }
	void SetPhysicsWorldGravityX(float PhysicsWorldGravityX) { m_PhysicsWorldGravityX = PhysicsWorldGravityX; }
	void SetPhysicsWorldGravityY(float PhysicsWorldGravityY) { m_PhysicsWorldGravityY = PhysicsWorldGravityY; }

	float GetPhysicsWorldPixToMeters() { return m_PhysicsWorldPixToMeters; }
	void SetPhysicsWorldPixToMeters(float PhysicsWorldPixToMeters) { m_PhysicsWorldPixToMeters = PhysicsWorldPixToMeters; }

	bool GetInheritsPhysicsWorldSettings() { return m_PhysicsWorldInheritSettings; }
	void SetInheritsPhysicsWorldSettings(bool PhysicsWorldInheritSettings) { m_PhysicsWorldInheritSettings = PhysicsWorldInheritSettings; }

	// Manipulate room settings
	int GetWidth() { return m_Width; }
	int GetHeight() { return m_Height; }
	void SetWidth(int Width) { m_Width = Width; }
	void SetHeight(int Height) { m_Height = Height; }

	bool GetIsPersistent() { return m_Persistent; }
	void SetIsPersistent(bool Persistent) { m_Persistent = Persistent; }

	bool GetInheritsBaseSettings() { return m_InheritSettings; }
	void SetInheritsBaseSettings(bool InheritSettings) { m_InheritSettings = InheritSettings; }

	// Manipulate view settings
	bool GetViewsEnabled() { return m_EnableViews; }
	void SetViewsEnabled(bool EnableViews) { m_EnableViews = EnableViews; }

	bool GetViewsClearDisplayBuffer() { return m_ViewsClearDisplayBuffer; }
	void SetViewsClearDisplayBuffer(bool ViewsClearDisplayBuffer) { m_ViewsClearDisplayBuffer = ViewsClearDisplayBuffer; }

	bool GetViewsClearBackground() { return m_ViewsClearBackground; }
	void SetViewsClearBackground(bool ViewsClearBackground) { m_ViewsClearBackground = ViewsClearBackground; }

	bool GetInheritsViewSettings() { return m_ViewsInheritSettings; }
	void SetInheritsViewSettings(bool ViewsInheritSettings) { m_ViewsInheritSettings = ViewsInheritSettings; }
};