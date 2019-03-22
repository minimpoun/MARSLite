#include "Source/Utility/ResouceContainer.h"

ResourceContainer& ResourceContainer::Get()
{
	static ResourceContainer _Container;
	return _Container;
}

ResourceContainer::ResourceContainer() : Fonts_OTF("Fonts", "otf"), Fonts_TTF("Fonts", "ttf"), Textures("Textures", "png"), Sounds("Sounds", "ogg")
{}