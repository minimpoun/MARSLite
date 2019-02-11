#include "Application.h"
#include "Utility/FileManager.hpp"
#include "Game/GameState.hpp"

using namespace MARS;

void Application::Shutdown()
{

}

Application::~Application()
{
	delete Window;

	while (!States.empty())
	{
		delete States.top();
		States.pop();
	}
}

void Application::Register(ApplicationSettings Settings, std::shared_ptr<Application>& OutApplication)
{
	std::shared_ptr<MARS::Application> _App = std::make_shared<MARS::Application>();
	
	if (_App)
	{
		_App->InitApplication(Settings.Title, Settings.Width, Settings.Height);
		_App->RegisterStates();
		
		OutApplication = _App;
	}
}

void Application::InitApplication(String Title, int w, int h)
{
	bool EnableFramerateLock = true;
	bool EnableVSync = false;
	int MaxFPS = 30;

{
	std::unique_ptr<FileManager> _FM = std::make_unique<FileManager>();
	if (_FM)
	{
		if (!_FM->LoadFile("../Engine/Config/Default.mars"))
		{
			LOG("Failed to load the Default MARS Config file")
		}
		else
		{
			LOG("Loaded Default MARS Config Files")		
		}	
	
		_FM->Get("Title", Title);

		_FM->Get("LimitFPS", EnableFramerateLock);

		_FM->Get("ResolutionWidth", w);
		_FM->Get("ResolutionHeight", h);

		_FM->Get("EnableVSync", EnableVSync);

		_FM->Get("MaxFPS", MaxFPS);
	}
}

	Window = new sf::RenderWindow(sf::VideoMode(w, h), Title);
	if (Window)
	{
		LOG("Window Created Successfully")
	
		Window->setVerticalSyncEnabled(EnableVSync);
		
		if (EnableFramerateLock)
		{
			Window->setFramerateLimit(MaxFPS);
		}
	}	
}

void Application::RegisterStates()
{
	States.push(new GameState(Window));
	States.top()->OnConstruct();
}

void Application::Run()
{
	while (Window && Window->isOpen() && !AwaitingExit)
	{
		Tick(); // Updates game code and events
		Render(); // Updates viewport
	}
}

void Application::Tick()
{
	Delta = DeltaClock.restart().asSeconds();
	
	HandleEvents();

	if (!States.empty())
	{
		States.top()->Refresh(Delta);
		
		if (States.top()->IsPendingKill())
		{
			States.top()->KillState();
			delete States.top();
			States.pop();
		}
	}
	else
	{
		// TODO implement proper close
		AwaitingExit = true;
		Event.type = sf::Event::Closed;
	}
}

void Application::Render()
{
	Window->clear();
	
	if (!States.empty())
	{
		States.top()->Draw(Window);
	}
	
	Window->display();
}

void Application::HandleEvents()
{
	while (Window->pollEvent(this->Event))
	{
		if (this->Event.type == sf::Event::Closed) Window->close();
	}
}

