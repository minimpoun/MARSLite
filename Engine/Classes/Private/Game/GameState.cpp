
#include <Classes/Public/Game/GameState.hpp>

#include "Classes/Public/Game/Actor.h"
#include "Classes/Public/Game/Character.h"

GameState::GameState(sf::RenderWindow* InWindow)
	: State(InWindow)
{

}

GameState::~GameState()
{
	delete TestPlayer;
}

void GameState::OnStateKilled()
{

}

void GameState::TickState(const float& DeltaTime)
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
	/** @TODO(Chrisr): This needs to be totally reworked
	 * @brief So, first off IDK why I set this up to call back into Actor.
	 * But the way this should work, is there needs to be an array of active input actors (characters)
	 * in the GameState; not in the actor base class.
	 * The SetupPlayerInput function inside of Actor should add itself to the list in the GameState.
	 * Since there always needs to be at least one active GameState, there can be a global GetGameState function.
	 * How I actually do this doesn't matter right now, but the way this currently works is awful.
	 **/
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
