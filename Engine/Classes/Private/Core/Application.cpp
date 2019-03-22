
#include <Classes/Public/Core/Application.h>

#include "Source/Utility/FileManager.hpp"
#include "Source/Utility/ResourceManager.hpp"
#include "Source/Utility/ResouceContainer.h"
#include "Classes/Public/Game/GameState.hpp"
#include "Classes/Public/GUI/MenuState.hpp"

using namespace MARS;

Application::Application()
{
	BaseGameState = nullptr;
	
	InitApplication();
	RegisterStates();
}

Application::~Application()
{
	LOG("Test")
}

void Application::Shutdown()
{
	delete Window;
	
	while (!States.empty())
	{
		delete States.top();
		States.pop();
	}
}

void Application::InitApplication(String Title, int w, int h)
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
		
		_FM->Get("ResolutionWidth", w);
		_FM->Get("ResolutionHeight", h);

		_FM->Get("EnableVSync", EnableVSync);
	}
}

	Window = new sf::RenderWindow(sf::VideoMode(w, h), Title);
	if (Window)
	{
		LOG("Target Created Successfully")
	
		Window->setVerticalSyncEnabled(EnableVSync);
		
		if (EnableFramerateLock)
		{
			Window->setFramerateLimit(MaxFPS);
		}
	}
}

void Application::RegisterStates()
{
	BaseGameState = new GameState(Window);
	States.push(new MenuState(Window));
	States.top()->OnConstruct();
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
	
	DrawFPS(bShowStats);
	
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