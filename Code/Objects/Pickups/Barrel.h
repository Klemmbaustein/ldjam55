#pragma once
#include <Objects/PhysicsObject.h>
#include <GENERATED/Barrel.h>

class Barrel : public PhysicsObject
{
public:
	BARREL_GENERATED("Pickups");

	virtual void Begin() override;
};