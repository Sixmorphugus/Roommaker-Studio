// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "SFMLCanvas.h"

enum ScrollMode
{
	UpDown,
	LeftRight,
	InOut
};

class RMSRoomView : public RMSSFMLCanvas
{
private:
	sf::Texture m_RmsLogoTexture;
	sf::Texture m_RmsGradientTexture;

	float m_ViewXOffset, m_ViewYOffset;
	float m_ViewZoom;
	bool m_PullingView;
	int m_LastMouseX, m_LastMouseY;

	ScrollMode m_ScrollMode;

public:
	RMSRoomView(wxWindow* Parent = NULL, wxWindowID Id = -1, const wxPoint& Position = wxDefaultPosition, const wxSize& Size = wxDefaultSize, long Style = 0);

protected:
	virtual sf::View GetViewSetup();

	void OnPaint(wxPaintEvent& event);
	void OnUpdateUI(wxUpdateUIEvent& event);

private:
	DECLARE_EVENT_TABLE()
};