#pragma once

#include "Common.h"

class Actor
{
public:

	Actor();
	~Actor();
	
	virtual void Tick(const float& DeltaTime) = 0;
	virtual void Draw(sf::RenderTarget* InTarget) = 0;
	
protected:
	
	float GetDelta() const;
	
	void SetMaxWalkSpeed(float& NewSpeed);
	
private:

	float MaxWalkSpeed = 100.f;
	float m_DeltaTime;
	
};