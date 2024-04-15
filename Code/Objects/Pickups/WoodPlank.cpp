#include "WoodPlank.h"

void WoodPlank::Begin()
{
	CreateObject("WoodPlank", Transform(0, 0, 0.35f));
	PickupName = "Wood Plank";
	InteractString = "Pick up " + PickupName;
}
