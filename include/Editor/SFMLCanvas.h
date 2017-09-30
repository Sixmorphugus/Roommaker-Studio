// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

#include "Platform.h"
#include "SFML/Graphics.hpp"

class RMSSFMLCanvas : public wxControl, public sf::RenderWindow
{
public:
	RMSSFMLCanvas(wxWindow* Parent = NULL, wxWindowID Id = -1, const wxPoint& Position = wxDefaultPosition, const wxSize& Size = wxDefaultSize, long Style = 0);
	virtual ~RMSSFMLCanvas() {};
	void SetDrawMode(bool onOrOff);

protected:
	virtual sf::View GetViewSetup();

	void OnIdle(wxIdleEvent&);
	void OnUpdateUI(wxUpdateUIEvent& event);
	void OnEraseBackground(wxEraseEvent&) {};

private:
	DECLARE_EVENT_TABLE()

	wxPaintDC* m_DrawLock;
};
