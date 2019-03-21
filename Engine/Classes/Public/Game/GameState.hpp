#pragma once

#include "Common.h"
#include "Classes/Public/Core/State.h"

class Character;
class Actor;
class Whatever;

class GameState : public State
{
public:

	GameState(sf::RenderWindow* InWindow);
	virtual ~GameState();

	virtual void OnConstruct() override;
	virtual void TickState(const float& DeltaTime) override;
	virtual void UpdateInput(const float& DeltaTime) override;
	virtual void Draw(sf::RenderTarget* InTarget = nullptr) override;
	virtual void OnStateKilled() override;
	virtual void UpdateState() override;

	void SetupPlayerInput(Actor* Player);
	
	
	
private:
	
	Character* TestPlayer;
	Whatever* TestWhatever;

};