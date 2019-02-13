#include <Classes/Game/Character.h>

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

Character::Character()
{
	Shape.setSize(sf::Vector2f(50.f, 50.f));
	Shape.setPosition(50.f, 50.f);
}
