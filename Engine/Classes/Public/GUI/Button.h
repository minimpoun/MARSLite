#pragma once

#include "Common.h"

enum class ButtonState
{
	Normal,
	Hovered,
	Clicked,
};

class Button
{
public:
	
	Button(const String& InText, const String& InFont, sf::Color InNormalColor, sf::Color InHoverColor, sf::Color InClickedColor, float xPos, float yPos, float Width, float Height);
	virtual ~Button();

	void Draw(sf::RenderTarget* Target);
	
	const bool& IsPressed() const { return CurrentState == ButtonState::Clicked; }
	
	void OnNormal();
	void OnClicked();
	void OnHovered();
	
	void Update(const sf::Vector2f& MousePos);
	
private:
	
	ButtonState CurrentState;
	
	sf::RectangleShape ButtonShape;
	sf::Text Text;
	
	sf::Color NormalColor;
	sf::Color HoverColor;
	sf::Color ClickedColor;
};