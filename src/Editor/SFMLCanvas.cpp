// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "SFMLCanvas.h"

#undef Status

// some extras needed for gtk
#ifdef __WXGTK__
	#include <gtk/gtk.h>
	#include <gdk/gdkx.h>
#endif

BEGIN_EVENT_TABLE(RMSSFMLCanvas, wxControl)
EVT_IDLE(RMSSFMLCanvas::OnIdle)
EVT_ERASE_BACKGROUND(RMSSFMLCanvas::OnEraseBackground)
EVT_UPDATE_UI(wxID_ANY, RMSSFMLCanvas::OnUpdateUI)
END_EVENT_TABLE()

RMSSFMLCanvas::RMSSFMLCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style) :
	wxControl(Parent, Id, Position, Size, Style)
{
	RMS_LogInfo("Initializing SFML Canvas...");

#ifdef __WXGTK__
	GtkWidget* widget = GetHandle();

	gtk_widget_realize(widget);
	gtk_widget_set_double_buffered(widget, false);

	GdkWindow* Win = gtk_widget_get_window( widget );

	XFlush(GDK_WINDOW_XDISPLAY(Win));

	sf::RenderWindow::create((sf::WindowHandle)GDK_WINDOW_XID(Win));
#else
	// Tested under Windows XP only (should work with X11
	// and other Windows versions - no idea about MacOS)
	sf::RenderWindow::create((sf::WindowHandle)GetHandle());
#endif

	m_DrawLock = nullptr;
}

sf::View RMSSFMLCanvas::GetViewSetup()
{
	sf::View ourView = getDefaultView();

	ourView.setSize(GetSize().GetX(), GetSize().GetY());
	ourView.setCenter(GetSize().GetX() / 2, GetSize().GetY() / 2);

	return ourView;
}

void RMSSFMLCanvas::OnIdle(wxIdleEvent&)
{
	// Send a paint message when the control is idle, to ensure maximum framerate
	Refresh();
}

void RMSSFMLCanvas::OnUpdateUI(wxUpdateUIEvent& event)
{
	// Because of how SFML handles default views, we'll need to make our own for the window element to work properly.
	setView(GetViewSetup());

	setSize(sf::Vector2u(GetSize().GetX(), GetSize().GetY()));
}

void RMSSFMLCanvas::SetDrawMode(bool onOrOff)
{
	if (onOrOff && !m_DrawLock) {
		m_DrawLock = new wxPaintDC(this);
	}
	else if (!onOrOff && m_DrawLock) {
		delete m_DrawLock;
		m_DrawLock = nullptr;
	}
}

