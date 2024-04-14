#pragma once
#include <GENERATED/Drill.h>
#include <Objects/PhysicsObject.h>

class Drill : public PhysicsObject
{
public:
	DRILL_GENERATED("Pickups");

	void Begin() override;
};