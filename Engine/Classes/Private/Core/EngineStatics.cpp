#include "Classes/Public/Core/EngineStatics.hpp"
#include "Classes/Public/Core/Application.h"

MARS::Application* EngineStatics::App = nullptr;

void EngineStatics::RegisterApplication(MARS::Application* InApp)
{
	if (InApp)
	{
		App = InApp;
	}
}

MARS::Application* EngineStatics::GetApplication()
{
	if (App)
	{
		return App;
	}
	
	FMT_LOG("Error, there is no valid application! Did you forget to call %s::RegisterApplication(MARS::Application*)?", __FUNCTION__)
	return nullptr;
}