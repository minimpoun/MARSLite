#pragma once

#include "Common.h"
#include "Classes/Public/GUI/Widget.h"

enum class ButtonState
{
	Normal,
	Hovered,
	Clicked,
};

class Button : public Widget
{
public:
	
	Button();
	virtual ~Button();

	void Draw(sf::RenderTarget* Target) override;
	virtual void SetStyle(const ButtonStyle& InStyle);
	virtual void Update(const sf::Vector2f& MousePos) override;
	
	void OnNormal();
	void OnClicked();
	void OnHovered();
	
private:
	
	ButtonState CurrentState;
	
	sf::RectangleShape ButtonShape;
	sf::Text Text;
	
	sf::Color NormalColor;
	sf::Color HoverColor;
	sf::Color ClickedColor;
};