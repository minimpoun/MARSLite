#pragma once

#include "Common.h"

class FileManager;

class Actor
{
public:
	
	Actor();
	
	virtual ~Actor();
	
	virtual void Tick(const float& DeltaTime);
	
	virtual void Draw(sf::RenderTarget* InTarget)
	{ }
	
	virtual void UpdatePlayerInput()
	{ }
	
	virtual void OnConstruct();
	
	std::vector<Actor*> GetAllInputActors() const { return InputActors; }

protected:
	
	virtual void SetupPlayerInput();
	
	float GetDelta() const;
	float GetMaxWalkSpeed() const { return MaxWalkSpeed; }
	
	void SetMaxWalkSpeed(float NewSpeed);
	
	void BindAction(String ActionName, std::function<void(float)> const& Callback);
	
	void BindAxis(String AxisName, void(Actor::*Axis)(float));
	
private:
	
	FileManager* FM;
	
	static std::vector<Actor*> InputActors;
	
	float MaxWalkSpeed = 200.f;
	float m_DeltaTime;
	
};