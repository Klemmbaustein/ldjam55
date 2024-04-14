#include "Milk.h"

void Milk::Begin()
{
	CreateObject("Milk", Transform(0, 0, 0.25f));
	PickupName = "Milk";
	InteractString = "Pick up " + PickupName;
}
