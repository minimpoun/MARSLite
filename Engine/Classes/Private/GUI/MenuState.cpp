#include "Classes/Public/GUI/MenuState.hpp"
#include "Classes/Public/GUI/Button.h"
#include "Classes/Public/GUI/Canvas.hpp"

MenuState::MenuState(sf::RenderWindow* InWindow) : State(InWindow)
{
	BackgroundImage.setSize(sf::Vector2f(InWindow->getSize().x, InWindow->getSize().y));
	BackgroundImage.setFillColor(sf::Color::Blue);
	
	StateName = "MenuState";
}

MenuState::~MenuState()
{

}

void MenuState::OnConstruct()
{
	TestCanvas = new Canvas();
}

void MenuState::TickState(const float& DeltaTime)
{
	UpdateMousePosition();
	
	// this is here to test the visibility rendering
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		GetCanvas()->GetWidget("TestButton")->SetVisibility(EVisibility::Hidden);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		GetCanvas()->GetWidget("TestButton")->SetVisibility(EVisibility::VisibleWithHitDetection);
	}
}

void MenuState::Draw(sf::RenderTarget* InTarget)
{
	if (!InTarget)
	{
		InTarget = this->Window;
	}
	
	InTarget->draw(this->BackgroundImage);
	TestCanvas->DrawCanvas(InTarget);
	TestCanvas->RefreshWidgets(MousePos_Viewport);
}

void MenuState::OnStateKilled()
{

}

void MenuState::UpdateInput(const float& Delta)
{

}

Canvas* MenuState::GetCanvas() const
{
	return TestCanvas;
}