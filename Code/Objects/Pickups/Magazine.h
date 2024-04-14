#pragma once
#include <GENERATED/Magazine.h>
#include <Objects/PhysicsObject.h>

class Magazine : public PhysicsObject
{
public:
	MAGAZINE_GENERATED("Pickups");

	void Begin() override;
};