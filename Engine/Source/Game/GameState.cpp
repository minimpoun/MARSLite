
#include <Classes/Game/GameState.hpp>

#include "Game/GameState.hpp"

using namespace MARS;

GameState::GameState(sf::RenderWindow* InWindow)
	: StateHandle(InWindow)
{

}

GameState::~GameState()
{

}

void GameState::OnStateKilled()
{
}

void GameState::Refresh(const float& DeltaTime)
{
	UpdateState();
	UpdateInput(DeltaTime);
}

void GameState::Draw(sf::RenderTarget* InTarget)
{

}

void GameState::UpdateInput(const float& DeltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		KillState();
	}
}

void GameState::UpdateState()
{

}
