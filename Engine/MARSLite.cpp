#include "MARSLite.h"

int main(int Argc, char** Argv)
{
	ApplicationSettings Settings;
	Settings.Title = "Test";
	Settings.Width = 1000;
	Settings.Height = 800;
	MARS::Application* App = new MARS::Application(Settings);
	if (App)
	{
		EngineStatics::RegisterApplication(App);
		App->Run();
		App->Shutdown();
	}
	
	return 0;
}