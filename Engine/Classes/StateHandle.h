#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <memory>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

#include "TypeHelpers.hpp"

namespace MARS
{
class StateHandle
{

public:

	StateHandle(sf::RenderWindow* InWindow);
	virtual ~StateHandle();
	
	const bool& IsPendingKill();
	
	virtual void Refresh(const float& DeltaTime) = 0;
	virtual void UpdateInput(const float& DeltaTime) = 0;
	virtual void Draw(sf::RenderTarget* InTarget = nullptr) = 0;
	virtual void UpdateState() = 0;
	virtual void OnStateKilled() = 0;
	
	virtual void KillState();
	
	
private:

	bool PendingKill;
	sf::RenderTarget* Window;
	std::vector<sf::Texture> Textures;
};
}