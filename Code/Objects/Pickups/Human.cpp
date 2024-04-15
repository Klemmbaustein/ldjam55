#include "Human.h"

void Human::Begin()
{
	CreateObject("CarriedHuman", Transform(0, 0, 0.75f));
	PickupName = "Human";
	InteractString = "Pick up " + PickupName;
}
