#pragma once

#include "StateHandle.h"

namespace MARS
{
class GameState : public MARS::StateHandle
{
public:

	GameState(sf::RenderWindow* InWindow);
	virtual ~GameState();

	virtual void DestroyState();

	virtual void Refresh(const float& DeltaTime);
	virtual void Draw(sf::RenderTarget* InTarget = nullptr);
};
}