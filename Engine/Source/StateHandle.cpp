
#include <Classes/StateHandle.h>

#include "StateHandle.h"

using namespace MARS;

StateHandle::StateHandle(sf::RenderWindow* InWindow)
{
	Window = InWindow;
	PendingKill = false;
}

StateHandle::~StateHandle()
{

}

const bool& StateHandle::IsPendingKill()
{
	return PendingKill;
}

void StateHandle::KillState()
{
	PendingKill = true;
	OnStateKilled();
}
