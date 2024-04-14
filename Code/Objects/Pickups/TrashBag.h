#pragma once
#include <GENERATED/TrashBag.h>
#include <Objects/PhysicsObject.h>

class TrashBag : public PhysicsObject
{
public:
	TRASHBAG_GENERATED("Pickups");

	void Begin() override;
};