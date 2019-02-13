#pragma once

#include "Common.h"
#include "Classes/Utility/NoCopy.h"
#include "Classes/Utility/NoMove.h"
#include "Classes/Utility/ResourceManager.hpp"

class ResourceContainer : public NoCopy, public NoMove
{
public:
	
	static ResourceContainer& Get();
	
	ResourceManager<sf::Font> Fonts;
	ResourceManager<sf::Texture> Textures;
	ResourceManager<sf::SoundBuffer> Sounds;

private:
	
	ResourceContainer();
};