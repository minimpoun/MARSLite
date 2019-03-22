
#include <Classes/Public/GUI/Button.h>
#include <Source/Utility/ResouceContainer.h>

Button::Button(const String& InText, const String& InFont, sf::Color InNormalColor, sf::Color InHoverColor,
				sf::Color InClickedColor, float xPos, float yPos, float Width, float Height)
{
	CurrentState = ButtonState::Normal;
	
	ButtonShape.setPosition(sf::Vector2f(xPos, yPos));
	ButtonShape.setSize(sf::Vector2f(Width, Height));
	
	Text.setString(InText);
	Text.setFont(ResourceContainer::Get().Fonts_OTF[InFont]);
	Text.setFillColor(sf::Color::Black);
	Text.setCharacterSize(32);
	Text.setPosition(ButtonShape.getPosition().x + (ButtonShape.getGlobalBounds().width / 2.f) - Text.getGlobalBounds().width / 2.f,
			         ButtonShape.getPosition().y + (ButtonShape.getGlobalBounds().height / 2.f) - Text.getGlobalBounds().height / 2.f);
	
	NormalColor = InNormalColor;
	HoverColor = InHoverColor;
	ClickedColor = InClickedColor;
	
	ButtonShape.setFillColor(NormalColor);
}

Button::~Button()
{

}

void Button::Draw(sf::RenderTarget* Target)
{
	Target->draw(ButtonShape);
	Target->draw(Text);
}

void Button::Update(const sf::Vector2f& MousePos)
{
	if (ButtonShape.getGlobalBounds().contains(MousePos) && CurrentState != ButtonState::Hovered)
	{
		CurrentState = ButtonState::Hovered;
		ButtonShape.setFillColor(HoverColor);

		OnHovered();
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			ButtonState::Clicked;
			ButtonShape.setFillColor(ClickedColor);
			
			OnClicked();
		}
	}
	
	if (!ButtonShape.getGlobalBounds().contains(MousePos) && CurrentState != ButtonState::Normal)
	{
		CurrentState = ButtonState::Normal;
		ButtonShape.setFillColor(NormalColor);
		
		OnNormal();
	}
}

void Button::OnNormal()
{
	LOG("Normal")
}

void Button::OnClicked()
{
	LOG("Clicked")
}

void Button::OnHovered()
{
	LOG("Hovered")
}