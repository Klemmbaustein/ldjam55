#pragma once
#include <Objects/PhysicsObject.h>
#include <GENERATED/Broom.h>

class Broom : public PhysicsObject
{
public:
	BROOM_GENERATED("Pickups");

	virtual void Begin() override;
};