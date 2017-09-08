// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "SFMLCanvas.h"

class rmsRoomView : public rmsSFMLCanvas
{
private:
	sf::Texture m_RmsLogoTexture;
	sf::Texture m_RmsGradientTexture;

public:
	rmsRoomView(wxWindow* Parent = NULL, wxWindowID Id = -1, const wxPoint& Position = wxDefaultPosition, const wxSize& Size = wxDefaultSize, long Style = 0);

private:
	DECLARE_EVENT_TABLE()

	void OnPaint(wxPaintEvent& event);
};