#include "Drill.h"

void Drill::Begin()
{
	CreateObject("Drill", Transform(0, 0, 0.25f));
	PickupName = "Drill";
	InteractString = "Pick up " + PickupName;
}
