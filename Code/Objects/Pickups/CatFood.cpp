#include "CatFood.h"

void CatFood::Begin()
{
	CreateObject("AnimalFood", Transform(0, 0, 0.15f));
	PickupName = "Cat Food";
	InteractString = "Pick up " + PickupName;
}
