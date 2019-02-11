#include "Classes/Application.h"


int main(int argc, char* argv[])
{
	std::shared_ptr<MARS::Application> App;
	
	MARS::Application::Register(ApplicationSettings(), App);
	App->Run();
	App->Shutdown();
	
	return 0;
}
