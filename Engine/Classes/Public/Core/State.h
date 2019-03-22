#pragma once

#include "Common.h"

class State
{

public:

	State(){}
	
	explicit State(sf::RenderWindow* InWindow);
	virtual ~State();
	
	const bool& IsPendingKill() { return PendingKill; }
	
	virtual void TickState(const float& DeltaTime) = 0;
	virtual void UpdateInput(const float& DeltaTime) = 0;
	virtual void Draw(sf::RenderTarget* InTarget = nullptr) = 0;
	virtual void OnStateKilled() = 0;
	virtual void OnConstruct() = 0;
	virtual void KillState();
	virtual void UpdateMousePosition();

protected:
	
	sf::Vector2i MousePos_Screen;
	sf::Vector2i MousePos_Window;
	sf::Vector2f MousePos_Viewport;
	
	sf::RenderWindow* Window;
	std::vector<sf::Texture> Textures;

private:

	bool PendingKill;
};