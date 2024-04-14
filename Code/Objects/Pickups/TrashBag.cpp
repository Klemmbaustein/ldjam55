#include "TrashBag.h"
#include <Objects/TrashCan.h>
#include <UI/GameUI.h>

void TrashBag::Begin()
{
	CreateObject("TrashBag", Transform(0, 0, 0.5f));
	PickupName = "Trash Bag";
	InteractString = "Pick up " + PickupName;
	if (!TrashCan::TrashExists)
	{
		GameUI::CurrentUI->GenerateTaskList();
		TrashCan::TrashExists = true;
	}
}
