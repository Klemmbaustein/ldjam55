#include "Barrel.h"

void Barrel::Begin()
{
	CreateObject("Barrel", Transform(0, 0, 0.5f));
	PickupName = "Barrel";
	InteractString = "Pick up " + PickupName;
}
