#pragma once

#include "Common.h"
#include "StateHandle.h"

class Character;
class Actor;

class GameState : public StateHandle
{
public:

	GameState(sf::RenderWindow* InWindow);
	virtual ~GameState();

	virtual void OnConstruct() override;
	virtual void Refresh(const float& DeltaTime) override;
	virtual void UpdateInput(const float& DeltaTime) override;
	virtual void Draw(sf::RenderTarget* InTarget = nullptr) override;
	virtual void OnStateKilled() override;
	virtual void UpdateState() override;

	void SetupPlayerInput(Actor* Player);
	
	
	
private:
	
	Character* TestPlayer;

};