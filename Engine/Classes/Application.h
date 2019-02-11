#pragma once

#include "Common.h"
#include "StateHandle.h"

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
	
	virtual ~Application();

	static void Register(ApplicationSettings Settings, std::shared_ptr<Application>& OutApplication);
	void ParseConsole(int cnt, char** cmd){}
	
	virtual void Render();
	virtual void Tick();
	virtual void Run();
	virtual void HandleEvents();
	
	virtual void Shutdown();

protected:

	virtual void InitApplication(String Title = "MARS Lite", int w = 800, int h = 600);

private:

	bool AwaitingExit;
	
	void RegisterStates();

	std::stack<StateHandle*> States;

	sf::Clock DeltaClock;
	float Delta;

	sf::RenderWindow* Window;
	sf::Event Event;
};
}