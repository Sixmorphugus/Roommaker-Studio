#pragma once

#include "Platform.h"

#include "SFML/Graphics.hpp"

class rmsSFMLCanvas : public wxControl, public sf::RenderWindow
{
public:

	rmsSFMLCanvas(wxWindow* Parent = NULL, wxWindowID Id = -1, const wxPoint& Position = wxDefaultPosition, const wxSize& Size = wxDefaultSize, long Style = 0);
	virtual ~rmsSFMLCanvas() {};
	void SetDrawMode(bool onOrOff);

private:

	DECLARE_EVENT_TABLE()

	virtual void OnPaint(wxPaintEvent& event);
	void OnIdle(wxIdleEvent&);
	void OnEraseBackground(wxEraseEvent&) {};

	wxPaintDC* m_DrawLock;
};
