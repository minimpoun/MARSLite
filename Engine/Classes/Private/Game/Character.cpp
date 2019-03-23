#include <Classes/Public/Game/Character.h>
#include <Classes/Public/Core/EngineStatics.hpp>
#include "Classes/Public/GUI/MenuState.hpp"
#include "Classes/Public/GUI/Canvas.hpp"

void Character::Tick(const float& DeltaTime)
{
	Actor::Tick(DeltaTime);
}

void Character::Draw(sf::RenderTarget* InTarget)
{
	InTarget->draw(Shape);
}

void Character::UpdatePlayerInput()
{
	BindAction("MoveForward", std::bind(&Character::MoveForward, this, std::placeholders::_1));
	BindAction("MoveBackward", std::bind(&Character::MoveBackward, this, std::placeholders::_1));
	BindAction("MoveLeft", std::bind(&Character::MoveLeft, this, std::placeholders::_1));
	BindAction("MoveRight", std::bind(&Character::MoveRight, this, std::placeholders::_1));
	BindAction("EndGame", std::bind(&Character::EndGame, this));
}

void Character::OnConstruct()
{
	Actor::OnConstruct();
	
}

void Character::MoveForward(float Val)
{
	Shape.move(0.f, -Val * GetMaxWalkSpeed() * GetDelta());
}

void Character::MoveBackward(float Val)
{
	Shape.move(0.f, Val * GetMaxWalkSpeed() * GetDelta());
}

void Character::MoveRight(float Val)
{
	Shape.move(Val * GetMaxWalkSpeed() * GetDelta(), 0.f);
}

void Character::MoveLeft(float Val)
{
	Shape.move(-Val * GetMaxWalkSpeed() * GetDelta(), 0.f);
}

void Character::SetupPlayerInput()
{
	Actor::SetupPlayerInput();
}

void Character::EndGame()
{
	// Constructs the MenuState and swaps to it.
	auto* _MenuState = EngineStatics::GetApplication()->ConstructState<MenuState>();
	if (_MenuState)
	{
		ButtonStyle _BS;
		_BS.Size = sf::Vector2f(100.f,100.f);
		_BS.Normal.WidgetColor = sf::Color::White;
		_BS.Hovered.WidgetColor = sf::Color::Blue;
		_BS.Clicked.WidgetColor = sf::Color::Green;
		_MenuState->GetCanvas()->CreateWidget<Button>("TestButton", _BS);
	}
}

Character::Character()
{
	Shape.setSize(sf::Vector2f(50.f, 50.f));
	Shape.setPosition(50.f, 50.f);
	Shape.setFillColor(sf::Color::Blue);
}
