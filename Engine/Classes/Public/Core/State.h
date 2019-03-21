#pragma once

#include "Common.h"

class State
{

public:

	State(sf::RenderWindow* InWindow);
	virtual ~State();
	
	const bool& IsPendingKill() { return PendingKill; }
	
	virtual void TickState(const float& DeltaTime) = 0;
	virtual void UpdateInput(const float& DeltaTime) = 0;
	virtual void Draw(sf::RenderTarget* InTarget = nullptr) = 0;
	virtual void UpdateState() = 0;
	virtual void OnStateKilled() = 0;
	virtual void OnConstruct() = 0;
	virtual void KillState();

protected:
	
	sf::RenderTarget* Window;
	std::vector<sf::Texture> Textures;

private:

	bool PendingKill;
};