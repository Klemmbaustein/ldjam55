#include "WoodPlank.h"

void WoodPlank::Begin()
{
	CreateObject("WoodPlank", Transform(0, 0, 0.25f));
	PickupName = "Wood Plank";
	InteractString = "Pick up " + PickupName;
}
