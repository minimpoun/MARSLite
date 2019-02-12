#include <Classes/Game/Actor.h>
#include "Utility/FileManager.hpp"

std::vector<Actor*> Actor::InputActors = {};

Actor::Actor()
{
}

Actor::~Actor()
{
	delete FM;
}

float Actor::GetDelta() const
{
	return m_DeltaTime;
}

void Actor::SetMaxWalkSpeed(float NewSpeed)
{
	MaxWalkSpeed = NewSpeed;
}

void Actor::OnConstruct()
{
	SetupPlayerInput();
}

void Actor::SetupPlayerInput()
{
	InputActors.push_back(this);
	FM = new FileManager;
	FM->LoadFile("../Engine/Config/DefaultInput.mars");
}

void Actor::BindAction(String ActionName, std::function<void(float)> const& Callback)
{
	if (FM)
	{
		int Key = -1;
		FM->Get(ActionName, Key);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(Key)))
		{
			std::invoke(Callback, 1.f);
		}
	}
}

void Actor::BindAxis(String AxisName, void (Actor::* Axis)(float))
{
}

void Actor::Tick(const float& DeltaTime)
{
	m_DeltaTime = DeltaTime;
}
