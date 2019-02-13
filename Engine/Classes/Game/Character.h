#pragma once

#include "Common.h"
#include "Game/Actor.h"

class Character : public Actor
{
public:

	Character();
	virtual ~Character() { }
	
	virtual void Tick(const float& DeltaTime) override;
	virtual void Draw(sf::RenderTarget* InTarget) override;
	virtual void UpdatePlayerInput() override;
	
	virtual void OnConstruct() override;

protected:
	
	virtual void SetupPlayerInput() override;
	
	void MoveForward(float Val);
	void MoveBackward(float Val);
	void MoveRight(float Val);
	void MoveLeft(float Val);
	
private:
	
	sf::RectangleShape Shape;
	
};