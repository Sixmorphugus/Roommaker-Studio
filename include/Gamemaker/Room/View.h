// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"

#include <rapidjson/document.h>

class GMRView
{
private:
	std::string m_Id;

	int m_HBorder;
	int m_VBorder;

	int m_HSpeed;
	int m_VSpeed;

	int m_XPort;
	int m_YPort;
	int m_WPort;
	int m_HPort;

	int m_XView;
	int m_YView;
	int m_WView;
	int m_HView;

	bool m_Inherit;

	bool m_Visible;

	class GMObject* m_Object;
	class GMRoom* m_Room;

private:
	void SetDefaults();

public:
	GMRView(GMRoom* Room); // default constructor
	GMRView(GMRoom* Room, rapidjson::Value& StoredView); // loaded room constructor

	virtual rapidjson::Document GetJSON() const;

	// Id
	std::string GetKey() { return m_Id; }

	GMRoom* GetRoom() { return m_Room; }

	GMObject* GetFollowObject() { return m_Object; }
	void SetFollowObject(GMObject* FollowObject) { m_Object = FollowObject; }

	// Viewport
	int GetXPort() const { return m_XPort; }
	int GetYPort() const { return m_YPort; }
	int GetWPort() const { return m_WPort; }
	int GetHPort() const { return m_HPort; }
	void SetXPort(int XPort) { m_XPort = XPort; }
	void SetYPort(int YPort) { m_YPort = YPort; }
	void SetWPort(int WPort) { m_WPort = WPort; }
	void SetHPort(int HPort) { m_HPort = HPort; }
	void SetPort(int XPort, int YPort, int WPort, int HPort) { SetXPort(XPort); SetYPort(YPort); SetWPort(WPort); SetHPort(HPort); }

	// View
	int GetXView() const { return m_XView; }
	int GetYView() const { return m_YView; }
	int GetWView() const { return m_WView; }
	int GetHView() const { return m_HView; }
	void SetXView(int XView) { m_XView = XView; }
	void SetYView(int YView) { m_YView = YView; }
	void SetWView(int WView) { m_WView = WView; }
	void SetHView(int HView) { m_HView = HView; }
	void SetView(int XView, int YView, int WView, int HView) { SetXView(XView); SetYView(YView); SetWView(WView); SetHView(HView); }

	// View Boarder
	int GetHBoarder() const { return m_HBorder; }
	int GetVBoarder() const { return m_VBorder; }
	void SetHBoarder(int HBoarder) { m_HBorder = HBoarder; }
	void SetVBoarder(int VBoarder) { m_VBorder = VBoarder; }
	void SetBoarder(int HBoarder, int VBoarder) { SetHBoarder(HBoarder); SetVBoarder(VBoarder); }

	// View Movement Speed
	int GetHSpeed() const { return m_HSpeed; }
	int GetVSpeed() const { return m_VSpeed; }
	void SetHSpeed(int HSpeed) { m_HSpeed = HSpeed; }
	void SetVSpeed(int VSpeed) { m_VSpeed = VSpeed; }
	void SetSpeed(int HSpeed, int VSpeed) { SetHSpeed(HSpeed); SetVSpeed(VSpeed); }

	// View Inheritance
	bool GetIsInherited() const { return m_Inherit; }
	void SetIsInherited(bool Inherit) { m_Inherit = Inherit; }

	// View Visibility
	bool GetIsVisible() const { return m_Visible; }
	void SetIsVisible(bool Visible) { m_Visible = Visible; }

	friend class GMRoom;
};
