// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "GM.h"
#include "Room/View.h"
#include "Room/Layer.h"

#include "SFML/Graphics.hpp"

#include <memory>

class GMRoom :
	public GMResource
{
private:
	// Room Content
	std::string m_CreationCode;
	GMRoom* m_ParentRoom;
	std::vector<std::shared_ptr<GMRLayer>> m_Layers;
	std::shared_ptr<GMRView> m_Views[8];
	std::vector<class GMRInstance*> m_InstanceCreationOrder;

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

	// Editor
	unsigned m_ActiveLayerIndex;

private:
	void SetDefaults();

public:
	//GMRoom(GMProject2* Project); // Create a new room
	GMRoom(GMProject2* Project, std::string Key, std::string DataPath); // Load an existing room

	virtual void Init() override;

	// Useful operations
	rapidjson::Document GetJSON() const;

	// Room stuff
	GMRoom* GetParentRoom() const { return m_ParentRoom; }
	void SetParentRoom(GMRoom* ParentRoom) { m_ParentRoom = ParentRoom; }

	std::string GetCreationCode() const { return m_CreationCode; }
	void SetCreationCode(std::string CreationCode) { m_CreationCode = CreationCode; }

	GMRView* GetView(unsigned i) const;

	unsigned GetNumLayers() const { return m_Layers.size(); }
	GMRLayer* GetLayer(unsigned i) const;

	void SetActiveLayerIndex(unsigned i);
	unsigned GetActiveLayerIndex(unsigned i) const;
	GMRLayer* GetActiveLayer() const;

	// Manipulate physics settings
	bool GetIsPhysicsWorld() const { return m_isPhysicsWorld; }
	void SetIsPhysicsWorld(bool IsPhysicsWorld) { m_isPhysicsWorld = IsPhysicsWorld; }

	float GetPhysicsWorldGravityX() const { return m_PhysicsWorldGravityX; }
	float GetPhysicsWorldGravityY() const { return m_PhysicsWorldGravityY; }
	void SetPhysicsWorldGravityX(float PhysicsWorldGravityX) { m_PhysicsWorldGravityX = PhysicsWorldGravityX; }
	void SetPhysicsWorldGravityY(float PhysicsWorldGravityY) { m_PhysicsWorldGravityY = PhysicsWorldGravityY; }

	float GetPhysicsWorldPixToMeters() const { return m_PhysicsWorldPixToMeters; }
	void SetPhysicsWorldPixToMeters(float PhysicsWorldPixToMeters) { m_PhysicsWorldPixToMeters = PhysicsWorldPixToMeters; }

	bool GetInheritsPhysicsWorldSettings() const { return m_PhysicsWorldInheritSettings; }
	void SetInheritsPhysicsWorldSettings(bool PhysicsWorldInheritSettings) { m_PhysicsWorldInheritSettings = PhysicsWorldInheritSettings; }

	// Manipulate room settings
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	void SetWidth(int Width) { m_Width = Width; }
	void SetHeight(int Height) { m_Height = Height; }
	void SetSize(int Width, int Height) { SetWidth(Width); SetHeight(Height); }

	bool GetIsPersistent() const { return m_Persistent; }
	void SetIsPersistent(bool Persistent) { m_Persistent = Persistent; }

	bool GetInheritsBaseSettings() const { return m_InheritSettings; }
	void SetInheritsBaseSettings(bool InheritSettings) { m_InheritSettings = InheritSettings; }

	// Manipulate view settings
	bool GetViewsEnabled() const { return m_EnableViews; }
	void SetViewsEnabled(bool EnableViews) { m_EnableViews = EnableViews; }

	bool GetViewsClearDisplayBuffer() const { return m_ViewsClearDisplayBuffer; }
	void SetViewsClearDisplayBuffer(bool ViewsClearDisplayBuffer) { m_ViewsClearDisplayBuffer = ViewsClearDisplayBuffer; }

	bool GetViewsClearBackground() const { return m_ViewsClearBackground; }
	void SetViewsClearBackground(bool ViewsClearBackground) { m_ViewsClearBackground = ViewsClearBackground; }

	bool GetInheritsViewSettings() const { return m_ViewsInheritSettings; }
	void SetInheritsViewSettings(bool ViewsInheritSettings) { m_ViewsInheritSettings = ViewsInheritSettings; }
};