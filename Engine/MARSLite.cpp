#include "MARSLite.h"

int main(int Argc, char** Argv)
{
	std::unique_ptr<MARS::Application> App = std::make_unique<MARS::Application>();
	App->Run();
	App->Shutdown();
	
	if (App)
	{
		App.release();
	}
	
	return 0;
}