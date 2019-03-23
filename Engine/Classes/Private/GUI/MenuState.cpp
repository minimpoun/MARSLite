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
	
	ButtonStyle _BS;
	_BS.Size = sf::Vector2f(100.f,100.f);
	_BS.Normal.WidgetColor = sf::Color::White;
	_BS.Hovered.WidgetColor = sf::Color::Blue;
	_BS.Clicked.WidgetColor = sf::Color::Green;
	GetCanvas()->CreateWidget<Button>("TestButton2", _BS);
}

void MenuState::TickState(const float& DeltaTime)
{
	UpdateMousePosition();
	
	// this is here to test the visibility rendering
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		auto* Button = GetCanvas()->GetWidget("TestButton");
		if (Button)
		{
			Button->SetVisibility(EVisibility::Hidden);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		ButtonStyle _BS;
		_BS.Size = sf::Vector2f(100.f,100.f);
		_BS.Normal.WidgetColor = sf::Color::White;
		_BS.Hovered.WidgetColor = sf::Color::Blue;
		_BS.Clicked.WidgetColor = sf::Color::Green;
		GetCanvas()->CreateWidget<Button>("TestButton2", _BS);
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