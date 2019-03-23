#pragma once

#include "Common.h"
#include "Classes/Public/Core/State.h"

class Button;
class Canvas;

class MenuState : public State
{
public:
	
	MenuState(){}
	
	explicit MenuState(sf::RenderWindow* InWindow);
	virtual ~MenuState();
	
	virtual void OnConstruct() override;
	virtual void TickState(const float& DeltaTime) override;
	virtual void Draw(sf::RenderTarget* InTarget = nullptr) override;
	virtual void OnStateKilled() override;
	virtual void UpdateInput(const float& Delta) override;

	Canvas* GetCanvas() const;
	
protected:



private:

	Canvas* TestCanvas;
	
	sf::RectangleShape BackgroundImage;
};