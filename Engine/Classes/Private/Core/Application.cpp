
#include <Classes/Public/Core/Application.h>

#include "Source/Utility/FileManager.hpp"
#include "Source/Utility/ResourceManager.hpp"
#include "Source/Utility/ResouceContainer.h"
#include "Classes/Public/Game/BaseGameState.hpp"
#include "Classes/Public/GUI/MenuState.hpp"

using namespace MARS;

Application::Application(const ApplicationSettings& Settings)
{
	GameState = nullptr;
	
	InitApplication(Settings.Title, Settings.Width, Settings.Height);
}

Application::~Application()
{
	LOG("Application Destroyed")
}

void Application::Shutdown()
{
	LOG("Application Shutting Down")
	
	delete Window;
	
	while (!States.empty())
	{
		delete States.top();
		States.pop();
	}
}

void Application::InitApplication(String Title, int32 Width, int32 Height)
{
	bool EnableFramerateLock = true;
	bool EnableVSync = false;
	int MaxFPS = 30;

	SetupFPS();
{
	std::unique_ptr<FileManager> _FM = std::make_unique<FileManager>();
	if (_FM)
	{
		if (!_FM->LoadFile("../Config/Default.mars"))
		{
			LOG("Failed to load the Default MARS Config file")
		}
		else
		{
			LOG("Loaded Default MARS Config Files")
		}
	
		_FM->Get("Title", Title);

		_FM->Get("LimitFPS", EnableFramerateLock);
		_FM->Get("MaxFPS", MaxFPS);
		_FM->Get("ShowStats", bShowStats);
		
		_FM->Get("ResolutionWidth", Width);
		_FM->Get("ResolutionHeight", Height);

		_FM->Get("EnableVSync", EnableVSync);
	}
}

	Window = new sf::RenderWindow(sf::VideoMode(Width, Height), Title);
	if (Window)
	{
		LOG("Target Created Successfully")
	
		Window->setVerticalSyncEnabled(EnableVSync);
		
		if (EnableFramerateLock)
		{
			Window->setFramerateLimit(MaxFPS);
		}
	}
	
	if (!GameState)
	{
		//GameState =
		ConstructState<MenuState>();
	}
}

bool Application::PushState(State* InState)
{
	if (InState)
	{
		States.push(InState);
		return true;
	}
	
	return false;
}

void Application::Run()
{
	while (Window && Window->isOpen())
	{
		Tick(); // Updates game code and events
		Render(); // Updates viewport
	}
}

void Application::Tick()
{
	UpdateDeltaTime();
	UpdateFrameCount();
	
	HandleEvents();

	if (!States.empty())
	{
		States.top()->TickState(Delta);
		
		if (States.top()->IsPendingKill())
		{
			States.top()->OnStateKilled();
			delete States.top();
			States.pop();
		}
	}
	else
	{
		LOG("ERROR: There is no State active! There must always be a State active!")
	}
}

void Application::Render()
{
	Window->clear();
	
	if (!States.empty())
	{
		States.top()->Draw(Window);
	}
	
	DrawFPS(bShowStats);
	
	Window->display();
}

void Application::HandleEvents()
{
	while (Window->pollEvent(this->Event))
	{
		if (this->Event.type == sf::Event::Closed)
		{
			Window->close();
		}
	}
}

void Application::UpdateDeltaTime()
{
	Delta = DeltaClock.restart().asSeconds();
}

void Application::UpdateFrameCount()
{
	FrameCount++;
	
	if (Delay.getElapsedTime().asSeconds() > 0.2)
	{
		FPS = FrameCount / FPSTimer.restart().asSeconds();
		FrameCount = 0;
		Delay.restart();
	}
}

void Application::SetupFPS()
{
	FPSText.move(0, 0);
	FPSText.setOutlineColor(sf::Color::Black);
	FPSText.setFillColor(sf::Color::Green);
	FPSText.setOutlineThickness(1);
	FPSText.setFont(ResourceContainer::Get().Fonts_OTF["Dosis-Light"]);
}

void Application::DrawFPS(bool bEnabled)
{
	if (bEnabled)
	{
		FPSText.setString("FPS: " + std::to_string((int)FPS));
		Window->draw(FPSText);
	}
}