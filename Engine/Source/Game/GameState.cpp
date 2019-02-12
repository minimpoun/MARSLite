
#include <Classes/Game/GameState.hpp>

#include "Game/Actor.h"
#include "Game/Character.h"

GameState::GameState(sf::RenderWindow* InWindow)
	: StateHandle(InWindow)
{

}

GameState::~GameState()
{
	delete TestPlayer;
}

void GameState::OnStateKilled()
{

}

void GameState::Refresh(const float& DeltaTime)
{
	UpdateState();
	UpdateInput(DeltaTime);
	
	TestPlayer->Tick(DeltaTime);
}

void GameState::Draw(sf::RenderTarget* InTarget)
{
	if (!InTarget)
	{
		InTarget = this->Window;
	}
	
	TestPlayer->Draw(InTarget);
}

void GameState::UpdateInput(const float& DeltaTime)
{
	for (size_t i = 0; i < TestPlayer->GetAllInputActors().size(); i++)
	{
		TestPlayer->GetAllInputActors()[i]->UpdatePlayerInput();
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		KillState();
	}
}

void GameState::UpdateState()
{

}

void GameState::OnConstruct()
{
	TestPlayer = new Character;
	TestPlayer->OnConstruct();
}
