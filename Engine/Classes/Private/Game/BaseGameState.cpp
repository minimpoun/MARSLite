
#include <Classes/Public/Game/BaseGameState.hpp>
#include <Classes/Public/Core/EngineStatics.hpp>

#include "Classes/Public/Game/Actor.h"
#include "Classes/Public/Game/Character.h"

BaseGameState::BaseGameState(sf::RenderWindow* InWindow)
	: State(InWindow)
{
	StateName = "BaseGameState";
}

BaseGameState::~BaseGameState()
{
	delete TestPlayer;
}

void BaseGameState::OnStateKilled()
{

}

void BaseGameState::TickState(const float& DeltaTime)
{
	UpdateMousePosition();
	UpdateInput(DeltaTime);
	
	TestPlayer->Tick(DeltaTime);
}

void BaseGameState::Draw(sf::RenderTarget* InTarget)
{
	if (!InTarget)
	{
		InTarget = this->Window;
	}
	
	TestPlayer->Draw(InTarget);
}

void BaseGameState::UpdateInput(const float& DeltaTime)
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
}

void BaseGameState::OnConstruct()
{
	TestPlayer = new Character;
	TestPlayer->OnConstruct();
}
