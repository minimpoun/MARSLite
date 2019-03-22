#include "Classes/Public/GUI/MenuState.hpp"
#include "Classes/Public/GUI/Button.h"

MenuState::MenuState(sf::RenderWindow* InWindow) : State(InWindow)
{
	BackgroundImage.setSize(sf::Vector2f(InWindow->getSize().x, InWindow->getSize().y));
	BackgroundImage.setFillColor(sf::Color::Black);
	
	TestButton = new Button("Test", "Dosis-Light", sf::Color::White, sf::Color::Blue, sf::Color::Black, 300, 300, 200, 100);
}

MenuState::~MenuState()
{

}

void MenuState::OnConstruct()
{

}

void MenuState::TickState(const float& DeltaTime)
{
	UpdateMousePosition();
	TestButton->Update(MousePos_Viewport);
}

void MenuState::Draw(sf::RenderTarget* InTarget)
{
	if (!InTarget)
	{
		InTarget = this->Window;
	}
	
	InTarget->draw(this->BackgroundImage);
	TestButton->Draw(InTarget);
}

void MenuState::OnStateKilled()
{

}

void MenuState::UpdateInput(const float& Delta)
{

}

