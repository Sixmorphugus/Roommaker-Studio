// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"

#include <rapidjson/document.h>

class GMView
{
private:
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

private:
	void SetDefaults();
	GMView(rapidjson::GenericObject<false, rapidjson::GenericValue<rapidjson::UTF8<>>>& StoredView); // loaded room constructor

public:
	GMView(); // default constructor

	// Viewport
	int GetXPort() { return m_XPort; }
	int GetYPort() { return m_YPort; }
	int GetWPort() { return m_WPort; }
	int GetHPort() { return m_HPort; }
	void SetXPort(int XPort) { m_XPort = XPort; }
	void SetYPort(int YPort) { m_YPort = YPort; }
	void SetWPort(int WPort) { m_WPort = WPort; }
	void SetHPort(int HPort) { m_HPort = HPort; }
	void SetPort(int XPort, int YPort, int WPort, int HPort) { SetXPort(XPort); SetYPort(YPort); SetWPort(WPort); SetHPort(HPort); }

	// View
	int GetXView() { return m_XView; }
	int GetYView() { return m_YView; }
	int GetWView() { return m_WView; }
	int GetHView() { return m_HView; }
	void SetXView(int XView) { m_XView = XView; }
	void SetYView(int YView) { m_YView = YView; }
	void SetWView(int WView) { m_WView = WView; }
	void SetHView(int HView) { m_HView = HView; }
	void SetView(int XView, int YView, int WView, int HView) { SetXView(XView); SetYView(YView); SetWView(WView); SetHView(HView); }

	// View Boarder
	int GetHBoarder() { return m_HBorder; }
	int GetVBoarder() { return m_VBorder; }
	void SetHBoarder(int HBoarder) { m_HBorder = HBoarder; }
	void SetVBoarder(int VBoarder) { m_VBorder = VBoarder; }
	void SetBoarder(int HBoarder, int VBoarder) { SetHBoarder(HBoarder); SetVBoarder(VBoarder); }

	// View Movement Speed
	int GetHSpeed() { return m_HSpeed; }
	int GetVSpeed() { return m_VSpeed; }
	void SetHSpeed(int HSpeed) { m_HSpeed = HSpeed; }
	void SetVSpeed(int VSpeed) { m_VSpeed = VSpeed; }
	void SetSpeed(int HSpeed, int VSpeed) { SetHSpeed(HSpeed); SetVSpeed(VSpeed); }

	// View Inheritance
	bool GetIsInherited() { return m_Inherit; }
	void SetIsInherited(bool Inherit) { m_Inherit = Inherit; }

	// View Visibility
	bool GetIsVisible() { return m_Visible; }
	void SetIsVisible(bool Visible) { m_Visible = Visible; }

	friend class GMRoom;
};
