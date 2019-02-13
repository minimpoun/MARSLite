#pragma once

#include "Common.h"

class Texture
{

public:

	Texture(String TexturePath);
	Texture(const Texture& Other);
	virtual ~Texture();
	
	bool Delete();

	
	
};