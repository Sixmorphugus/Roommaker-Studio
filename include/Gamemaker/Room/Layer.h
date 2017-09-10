// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"

#include <rapidjson/document.h>
#include <SFML/Graphics.hpp>

class GMLayer
{
private:
	std::string m_Id;
	std::string m_Name;
	int m_Depth;

	int m_GridX;
	int m_GridY;

	bool m_HierarchyFrozen;
	bool m_HierarchyVisible;

	bool m_InheritLayerDepth;
	bool m_InheritLayerSettings;
	bool m_InheritSubLayers;
	bool m_InheritVisibility;

	class GMRoom* m_Room;
	GMLayer* m_Parent;

	bool m_SerialiseFrozen;
	bool m_UserdefinedDepth;

	bool m_Visible;

private:
	void SetDefaults(GMRoom* Room);
	GMLayer(GMRoom* Room, rapidjson::GenericObject<false, rapidjson::GenericValue<rapidjson::UTF8<>>>& StoredView); // loaded room constructor

public:
	GMLayer(GMRoom* Room); // default constructor

	virtual void DrawLayer(sf::RenderTarget& Target) {}

	std::string GetId() { return m_Id; }

	std::string GetName() { return m_Name; }
	void SetName(std::string Name) { m_Name = Name; }
	
	int GetDepth() { return m_Depth; }
	void SetDepth(int Depth) { m_Depth = Depth; }

	int GetGridX() { return m_GridX; }
	void SetGridX(int GridX) { m_GridX = GridX; }
	int GetGridY() { return m_GridY; }
	void SetGridY(int GridY) { m_GridY = GridY; }

	bool GetHierarchyIsFrozen() { return m_HierarchyFrozen; }
	void SetHierarchyIsFrozen(bool HierarchyFrozen) { m_HierarchyFrozen = HierarchyFrozen; }
	bool GetHierarchyVisible() { return m_HierarchyVisible; }
	void SetHierarchyVisible(bool HierarchyVisible) { m_HierarchyVisible = HierarchyVisible; }

	bool GetInheritsLayerDepth() { return m_InheritLayerDepth; }
	bool GetInheritsLayerSettings() { return m_InheritLayerSettings; }
	bool GetInheritsSubLayers() { return m_InheritSubLayers; }
	bool GetInheritsVisibility() { return m_InheritVisibility; }
	void SetInheritsLayerDepth(bool InheritLayerDepth) { m_InheritLayerDepth = InheritLayerDepth; }
	void SetInheritsLayerSettings(bool InheritsLayerSettings) { m_InheritLayerSettings = InheritsLayerSettings; }
	void SetInheritsSubLayers(bool InheritSubLayers) { m_InheritSubLayers = InheritSubLayers; }
	void SetInheritsVisibility(bool InheritVisibility) { m_InheritVisibility = InheritVisibility; }

	GMRoom* GetRoom() { return m_Room; }
	GMLayer* GetParent() { return m_Parent; }

	bool GetDoesSerializeFrozen() { return m_SerialiseFrozen; }
	void SetDoesSerializeFrozen(bool SerializeFrozen) { m_SerialiseFrozen = SerializeFrozen; }

	bool GetIsDepthUserDefined() { return m_UserdefinedDepth; }
	void SetIsDepthUserDefined(bool UserdefinedDepth) { m_UserdefinedDepth = UserdefinedDepth; }

	bool GetIsVisible() { return m_Visible; }
	void SetIsVisible(bool Visible) { m_Visible = Visible; }

	friend GMRoom;
};