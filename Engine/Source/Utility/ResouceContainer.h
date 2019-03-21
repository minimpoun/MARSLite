#pragma once

#include "Common.h"
#include "NoCopy.h"
#include "NoMove.h"
#include "ResourceManager.hpp"

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