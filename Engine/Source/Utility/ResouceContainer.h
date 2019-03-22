#pragma once

#include "Common.h"
#include "NoCopy.h"
#include "NoMove.h"
#include "ResourceManager.hpp"

class ResourceContainer : public NoCopy, public NoMove
{
public:
	
	static ResourceContainer& Get();
	
	/**@NOTE(Chrisr): This is a problem I just realized with my resource manager. It's great until you need to support multiple file types.
	 * So yeah, I need to try and come up with a way to better support multiple file types without having to have a separate
	 * ResourceManager instance for each type of asset.
	 **/
	ResourceManager<sf::Font> Fonts_OTF;
	ResourceManager<sf::Font> Fonts_TTF;
	ResourceManager<sf::Texture> Textures;
	ResourceManager<sf::SoundBuffer> Sounds;

private:
	
	ResourceContainer();
};