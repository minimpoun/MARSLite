#pragma once

#include "Common.h"
#include "Application.h"

class Application;

class EngineStatics
{
public:

	static void RegisterApplication(MARS::Application* InApp);
	
	static MARS::Application* GetApplication();


private:
	
	static MARS::Application* App;
};