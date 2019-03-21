#include "Source/Utility/ResouceContainer.h"

ResourceContainer& ResourceContainer::Get()
{
	static ResourceContainer _Container;
	return _Container;
}

ResourceContainer::ResourceContainer() : Fonts("Fonts", "ttf"), Textures("Textures", "png"), Sounds("Sounds", "ogg")
{}