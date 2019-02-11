
#include <Classes/Game/Actor.h>

#include "Classes/Game/Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

float Actor::GetDelta() const
{
	return m_DeltaTime;
}

void Actor::SetMaxWalkSpeed(float& NewSpeed)
{
	MaxWalkSpeed = NewSpeed;
}