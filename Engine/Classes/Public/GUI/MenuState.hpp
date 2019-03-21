#pragma once

#include "Common.h"
#include "Classes/Public/Core/State.h"

class MenuState : public State
{
public:
	
	MenuState(sf::RenderWindow* InWindow);
	virtual ~MenuState();
	
	virtual void OnConstruct() override;
	virtual void TickState(const float& DeltaTime) override;
	virtual void UpdateInput(const float& DeltaTime) override;
	virtual void Draw(sf::RenderTarget* InTarget = nullptr) override;
	virtual void OnStateKilled() override;
	virtual void UpdateState() override;
};