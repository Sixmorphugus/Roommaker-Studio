// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"

#include <rapidjson/document.h>
#include <SFML/Graphics.hpp>

class GMRLayer
{
protected:
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
	GMRLayer* m_Parent;

	bool m_SerialiseFrozen;
	bool m_UserdefinedDepth;

	bool m_Visible;

private:
	void SetDefaults(GMRoom* Room);

public:
	GMRLayer(GMRoom* Room); // default constructor
	GMRLayer(GMRoom* Room, rapidjson::Value& StoredLayer); // loaded room constructor

	virtual void Draw(sf::RenderTarget& Target) const;
	virtual void DrawActive(sf::RenderTarget& Target);
	virtual rapidjson::Document GetJSON() const;

	std::string GetKey() const { return m_Id; }

	std::string GetName() const { return m_Name; }
	void SetName(std::string Name) { m_Name = Name; }
	
	int GetDepth() const { return m_Depth; }
	void SetDepth(int Depth) { m_Depth = Depth; }

	int GetGridX() const { return m_GridX; }
	void SetGridX(int GridX) { m_GridX = GridX; }
	int GetGridY() const { return m_GridY; }
	void SetGridY(int GridY) { m_GridY = GridY; }

	bool GetHierarchyIsFrozen() const { return m_HierarchyFrozen; }
	void SetHierarchyIsFrozen(bool HierarchyFrozen) { m_HierarchyFrozen = HierarchyFrozen; }
	bool GetHierarchyVisible() const { return m_HierarchyVisible; }
	void SetHierarchyVisible(bool HierarchyVisible) { m_HierarchyVisible = HierarchyVisible; }

	bool GetInheritsLayerDepth() const { return m_InheritLayerDepth; }
	bool GetInheritsLayerSettings() { return m_InheritLayerSettings; }
	bool GetInheritsSubLayers() const { return m_InheritSubLayers; }
	bool GetInheritsVisibility() const { return m_InheritVisibility; }
	void SetInheritsLayerDepth(bool InheritLayerDepth) { m_InheritLayerDepth = InheritLayerDepth; }
	void SetInheritsLayerSettings(bool InheritsLayerSettings) { m_InheritLayerSettings = InheritsLayerSettings; }
	void SetInheritsSubLayers(bool InheritSubLayers) { m_InheritSubLayers = InheritSubLayers; }
	void SetInheritsVisibility(bool InheritVisibility) { m_InheritVisibility = InheritVisibility; }

	GMRoom* GetRoom() const { return m_Room; }
	GMRLayer* GetParent() const { return m_Parent; }

	bool GetDoesSerializeFrozen() const { return m_SerialiseFrozen; }
	void SetDoesSerializeFrozen(bool SerializeFrozen) { m_SerialiseFrozen = SerializeFrozen; }

	bool GetIsDepthUserDefined() const { return m_UserdefinedDepth; }
	void SetIsDepthUserDefined(bool UserdefinedDepth) { m_UserdefinedDepth = UserdefinedDepth; }

	bool GetIsVisible() const { return m_Visible; }
	void SetIsVisible(bool Visible) { m_Visible = Visible; }
};