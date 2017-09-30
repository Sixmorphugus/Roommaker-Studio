// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "RoomView.h"

#include "Editor.h"
#include "Room.h"

using namespace std;

BEGIN_EVENT_TABLE(RMSRoomView, RMSSFMLCanvas)
EVT_PAINT(RMSRoomView::OnPaint)
EVT_UPDATE_UI(wxID_ANY, RMSRoomView::OnUpdateUI)
END_EVENT_TABLE()

RMSRoomView::RMSRoomView(wxWindow* Parent /*= NULL*/, wxWindowID Id /*= -1*/, const wxPoint& Position /*= wxDefaultPosition*/, const wxSize& Size /*= wxDefaultSize*/, long Style /*= 0*/)
	: RMSSFMLCanvas(Parent, Id, Position, Size, Style)
{
	m_RmsLogoTexture.loadFromFile("base/GMS2.png");
	m_RmsGradientTexture.loadFromFile("base/gradient.png");

	m_RmsGradientTexture.setRepeated(true);

	m_ViewXOffset = 0.f;
	m_ViewYOffset = 0.f;

	m_LastMouseX = 0;
	m_LastMouseY = 0;

	m_ViewZoom = 1.f;

	m_ScrollMode = UpDown;

	m_PullingView = false;
}

sf::View RMSRoomView::GetViewSetup()
{
	auto StdView = RMSSFMLCanvas::GetViewSetup();

	StdView.setCenter(0, 0);
	StdView.move(m_ViewXOffset, m_ViewYOffset);
	StdView.zoom(m_ViewZoom);

	CamPos = StdView.getCenter() - sf::Vector2f(StdView.getSize().x / 2, StdView.getSize().y / 2);

	return StdView;
}

void RMSRoomView::OnPaint(wxPaintEvent& event)
{
	SetDrawMode(true);

	GMRoom* OpenRoom = wxGetApp().GetOpenRoom();
	
	if (OpenRoom)
	{
		// draw background black
		clear(sf::Color(150, 150, 150));

		// Draw each layer of the room.
		for (unsigned i = 0; i < OpenRoom->GetNumLayers(); i++)
		{
			OpenRoom->GetLayer(i)->Draw(*this);
		}

		OpenRoom->GetActiveLayer()->DrawActive(*this);

		// @todo If this layer is selected draw its grid
	}
	else
	{
		// No room is open.

		// draw background white
		clear(sf::Color(255, 255, 255));

		// draw gradient
		sf::Sprite GMS2Grad(m_RmsGradientTexture);
		GMS2Grad.setPosition(0, getSize().y);
		GMS2Grad.setOrigin(0, m_RmsGradientTexture.getSize().y);
		GMS2Grad.setScale((float)getSize().x / (float)m_RmsGradientTexture.getSize().x, 1);

		draw(GMS2Grad);

		// draw GMS2 logo
		sf::Sprite GMS2Sprite(m_RmsLogoTexture);
		GMS2Sprite.setPosition(getSize().x / 2U, getSize().y / 2U);
		GMS2Sprite.setOrigin(m_RmsLogoTexture.getSize().x / 2U, m_RmsLogoTexture.getSize().y / 2U);

		draw(GMS2Sprite);
	}

	display();
	
	SetDrawMode(false);
}

void RMSRoomView::OnUpdateUI(wxUpdateUIEvent& event)
{
	RMSSFMLCanvas::OnUpdateUI(event);

	GMRoom* OpenRoom = wxGetApp().GetOpenRoom();

	if (OpenRoom)
	{
		// detect SFML input
		sf::Event evt;
		while (pollEvent(evt))
		{
			if (evt.type == sf::Event::KeyPressed)
			{
				if (evt.key.code == sf::Keyboard::LShift)
				{
					m_ScrollMode = LeftRight;
				}
				else if (evt.key.code == sf::Keyboard::LControl)
				{
					m_ScrollMode = InOut;
				}
			}
			else if (evt.type == sf::Event::KeyReleased)
			{
				if (evt.key.code == sf::Keyboard::LShift || evt.key.code == sf::Keyboard::LControl)
				{
					m_ScrollMode = UpDown;
				}
			}
			else if (evt.type == sf::Event::MouseButtonPressed)
			{
				if (evt.mouseButton.button == sf::Mouse::Middle)
				{
					m_PullingView = true;
				}
			}
			else if (evt.type == sf::Event::MouseButtonReleased)
			{
				if (evt.mouseButton.button == sf::Mouse::Middle)
				{
					m_PullingView = false;
				}
			}
			else if (evt.type == sf::Event::MouseMoved)
			{
				if (m_PullingView)
				{
					m_ViewXOffset += (m_LastMouseX - (float)evt.mouseMove.x) * m_ViewZoom;
					m_ViewYOffset += (m_LastMouseY - (float)evt.mouseMove.y) * m_ViewZoom;
				}

				m_LastMouseX = evt.mouseMove.x;
				m_LastMouseY = evt.mouseMove.y;
			}
			else if (evt.type == sf::Event::MouseWheelScrolled)
			{
				if (m_ScrollMode == UpDown) 
				{
					m_ViewYOffset -= evt.mouseWheelScroll.delta * (20 * m_ViewZoom);
				}
				else if (m_ScrollMode == LeftRight)
				{
					m_ViewXOffset -= evt.mouseWheelScroll.delta * (20 * m_ViewZoom);
				}
				else if (m_ScrollMode == InOut)
				{
					sf::Vector2f mouseWorldBeforeZoom(sf::Vector2f(m_LastMouseX * m_ViewZoom, m_LastMouseY * m_ViewZoom) + CamPos);

					m_ViewZoom -= evt.mouseWheelScroll.delta > 0 ? .2f : -.2f;

					if (m_ViewZoom < 0.2f) m_ViewZoom = 0.2f;
					if (m_ViewZoom > 2.0f) m_ViewZoom = 2.0f;
					
					GetViewSetup(); // hack

					sf::Vector2f mouseWorldAfterZoom(sf::Vector2f(m_LastMouseX * m_ViewZoom, m_LastMouseY * m_ViewZoom) + CamPos);

					// move towards where you're zooming to
					RMS_LogInfo(to_string((mouseWorldBeforeZoom - mouseWorldAfterZoom).x) + " " + to_string((mouseWorldBeforeZoom - mouseWorldAfterZoom).y));

					m_ViewXOffset += (mouseWorldBeforeZoom - mouseWorldAfterZoom).x;
					m_ViewYOffset += (mouseWorldBeforeZoom - mouseWorldAfterZoom).y;
				}
			}
		}
	}
	else
	{
		m_ViewXOffset = getSize().x / 2;
		m_ViewYOffset = getSize().y / 2;
		m_ViewZoom = 1.f;
	}
}
