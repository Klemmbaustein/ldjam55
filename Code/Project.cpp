#include <string>
#include "Sounds.h"

namespace Project
{
	bool UseNetworkFunctions = false;

	// This is the name of the current project
	const char* ProjectName = "Sacrificed";

	// This function returns the map that will be loaded when the game is opened
	std::string GetStartupScene()
	{
#if RELEASE
		return "Menu";
#endif
		return "MainScene";
	}
	
	// This function will be called on startup.
	void OnLaunch()
	{
#if !EDITOR
		Sounds::LoadAll();
#endif
	}
}