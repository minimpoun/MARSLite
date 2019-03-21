
#include <Classes/State.h>

#include "State.h"

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
