#include "Magazine.h"

void Magazine::Begin()
{
	CreateObject("Magazine", Transform(0, 0, 0.25f));
	PickupName = "Magazine";
	InteractString = "Pick up " + PickupName;
}
