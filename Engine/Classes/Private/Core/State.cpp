
#include <Classes/Public/Core/State.h>

#include "Classes/Public/Core/State.h"

State::State(sf::RenderWindow* InWindow)
{
	Window = InWindow;
	PendingKill = false;
}

State::~State()
{

}

void State::KillState()
{
	PendingKill = true;
}

void State::UpdateMousePosition()
{
	MousePos_Screen = sf::Mouse::getPosition();
	MousePos_Window = sf::Mouse::getPosition(*Window);
	MousePos_Viewport = this->Window->mapPixelToCoords(sf::Mouse::getPosition(*this->Window));
}