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

	virtual void DestroyState() = 0;

	virtual void Refresh(const float& DeltaTime) = 0;
	virtual void Draw(sf::RenderTarget* InTarget = nullptr) = 0;

private:

	sf::RenderTarget* Window;
	std::vector<sf::Texture> Textures;
};
}