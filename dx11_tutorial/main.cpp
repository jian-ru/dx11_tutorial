#include "systemclass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdline, int nCmdshow)
{
	SystemClass *sys;
	bool result;

	// create the system object
	sys = new SystemClass;
	if (!sys)
	{
		return 1;
	}
	
	// initialize and run the system object
	result = sys->initialize();
	if (result)
	{
		sys->run();
	}

	// Shutdown and release the system object
	sys->shutdown();
	delete sys;
	sys = NULL;

	return 0;
}