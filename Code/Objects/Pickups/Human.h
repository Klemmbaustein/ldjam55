#pragma once
#include <Objects/PhysicsObject.h>
#include <GENERATED/Human.h>

class Human : public PhysicsObject
{
public:
	HUMAN_GENERATED("Pickups");

	virtual void Begin() override;
};