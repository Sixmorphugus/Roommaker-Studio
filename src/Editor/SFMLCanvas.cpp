#include "SFMLCanvas.h"

#undef Status

// some extras needed for gtk
#ifdef __WXGTK__
	#include <gtk/gtk.h>
	#include <gdk/gdkx.h>
#endif

BEGIN_EVENT_TABLE(rmsSFMLCanvas, wxControl)
EVT_IDLE(rmsSFMLCanvas::OnIdle)
EVT_ERASE_BACKGROUND(rmsSFMLCanvas::OnEraseBackground)
END_EVENT_TABLE()

rmsSFMLCanvas::rmsSFMLCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style) :
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

	Bind(wxEVT_PAINT, &rmsSFMLCanvas::OnPaint, this);
}

void rmsSFMLCanvas::OnPaint(wxPaintEvent& event)
{
	SetDrawMode(true);

	clear(sf::Color::Black);
	display();

	SetDrawMode(false);
}

void rmsSFMLCanvas::OnIdle(wxIdleEvent&)
{
	// Send a paint message when the control is idle, to ensure maximum framerate
	Refresh();
}

void rmsSFMLCanvas::SetDrawMode(bool onOrOff)
{
	if (onOrOff && !m_DrawLock) {
		m_DrawLock = new wxPaintDC(this);
	}
	else if (!onOrOff && m_DrawLock) {
		delete m_DrawLock;
		m_DrawLock = nullptr;
	}
}