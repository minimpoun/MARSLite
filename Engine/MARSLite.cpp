#include "MARSLite.h"

int main(int Argc, char** Argv)
{
	std::unique_ptr<MARS::Application> App = std::make_unique<MARS::Application>();
	if (App)
	{
		App->Run();
		App->Shutdown();
	}
	
	App.release();
	
	return 0;
}