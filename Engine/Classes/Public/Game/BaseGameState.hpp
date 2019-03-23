#pragma once

#include "Common.h"
#include "Classes/Public/Core/State.h"

class Character;
class Actor;
class Whatever;

class BaseGameState : public State
{
public:
	
	BaseGameState(){}

	explicit BaseGameState(sf::RenderWindow* InWindow);
	virtual ~BaseGameState();

	virtual void OnConstruct() override;
	virtual void TickState(const float& DeltaTime) override;
	virtual void UpdateInput(const float& DeltaTime) override;
	virtual void Draw(sf::RenderTarget* InTarget = nullptr) override;
	virtual void OnStateKilled() override;

	void SetupPlayerInput(Actor* Player);
	
	
	
private:
	
	Character* TestPlayer;
	Whatever* TestWhatever;

};