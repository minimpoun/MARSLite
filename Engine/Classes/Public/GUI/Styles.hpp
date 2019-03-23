#pragma once

#include "Common.h"

struct Style
{
	sf::Vector2f Size;
};

struct WidgetStyle
{
	sf::Color WidgetColor;
	sf::Texture WidgetTexture;
};

struct ButtonStyle : public Style
{
	WidgetStyle Normal;
	WidgetStyle Hovered;
	WidgetStyle Clicked;
};