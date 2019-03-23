#pragma once

#include "Common.h"
#include "Classes/Public/Core/State.h"

class BaseGameState;

struct ApplicationSettings
{
	ApplicationSettings()
	{
		this->Title = "null";
		Width = -1;
		Height = -1;
	}

	ApplicationSettings(String Title)
	{
		this->Title = Title;
		Width = 800;
		Height = 600;
	}

	ApplicationSettings(String Title, const int32& Width, const int32& Height)
	{
		this->Title = Title;
		this->Width = Width;
		this->Height= Height;
	}

	String Title;
	int32 Width, Height;
};

namespace MARS
{
class Application
{
public:
	
	Application(const ApplicationSettings& Settings);
	virtual ~Application();

	void ParseConsole(int cnt, char** cmd){}
	
	bool PushState(State* InState);
	
	virtual void Run();
	virtual void Shutdown();

	State* TryGetState() const
	{
		return States.top();
	}
	
	template<typename T>
	T* ConstructState()
	{
		T* _T = new T(Window);
		if (PushState(_T))
		{
			States.top()->OnConstruct();
			return _T;
		}
		
		return nullptr;
	}
	
protected:
	
	virtual void HandleEvents();
	virtual void Render();
	virtual void Tick();
	virtual void InitApplication(String Title, int32 Width, int32 Height);
	
private:

	void DrawFPS(bool bEnabled);
	
	void SetupFPS();
	
	void UpdateDeltaTime();
	void UpdateFrameCount();
	
	bool bShowStats;
	
	BaseGameState* GameState;
	
	std::stack<State*> States;
	
	sf::Clock DeltaClock;
	float Delta;

	sf::RenderWindow* Window;
	sf::Event Event;
	
	sf::Text FPSText;
	sf::Clock Delay;
	sf::Clock FPSTimer;
	
	float FPS;
	int64 FrameCount;
};
}