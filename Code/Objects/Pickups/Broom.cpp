#include "Broom.h"

void Broom::Begin()
{
	CreateObject("Broom", Transform(0, 0, 0.5f));
	PickupName = "Broom";
	InteractString = "Pick up " + PickupName;
}
