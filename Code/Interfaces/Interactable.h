#pragma once
#include <string>

class Interactable
{
public:
	virtual void OnInteract() = 0;

	std::string InteractString;
	bool CanInteract = true;
};