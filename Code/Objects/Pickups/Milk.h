#pragma once
#include <GENERATED/Milk.h>
#include <Objects/PhysicsObject.h>

class Milk : public PhysicsObject
{
public:
	MILK_GENERATED("Pickups");

	void Begin() override;
};