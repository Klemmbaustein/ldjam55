#pragma once
#include <GENERATED/WoodPlank.h>
#include <Objects/PhysicsObject.h>

class WoodPlank : public PhysicsObject
{
public:
	WOODPLANK_GENERATED("Pickups");

	void Begin() override;
};