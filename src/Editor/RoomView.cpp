// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "RoomView.h"

#include "Editor.h"
#include "Room.h"

using namespace std;

BEGIN_EVENT_TABLE(RMSRoomView, RMSSFMLCanvas)
EVT_PAINT(RMSRoomView::OnPaint)
END_EVENT_TABLE()

RMSRoomView::RMSRoomView(wxWindow* Parent /*= NULL*/, wxWindowID Id /*= -1*/, const wxPoint& Position /*= wxDefaultPosition*/, const wxSize& Size /*= wxDefaultSize*/, long Style /*= 0*/)
	: RMSSFMLCanvas(Parent, Id, Position, Size, Style)
{
	m_RmsLogoTexture.loadFromFile("base/GMS2.png");
	m_RmsGradientTexture.loadFromFile("base/gradient.png");

	m_RmsGradientTexture.setRepeated(true);
}

void RMSRoomView::OnPaint(wxPaintEvent& event)
{
	SetDrawMode(true);

	GMRoom* OpenRoom = wxGetApp().GetOpenRoom();
	
	if (OpenRoom)
	{
		// draw background black
		clear(sf::Color(0, 0, 0));

		// Draw each layer of the room.
		for (unsigned i = 0; i < OpenRoom->GetNumLayers(); i++)
		{
			OpenRoom->GetLayer(i)->Draw(*this);
		}

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