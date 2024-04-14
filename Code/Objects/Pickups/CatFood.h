#pragma once
#include <Objects/PhysicsObject.h>
#include <GENERATED/CatFood.h>

class CatFood : public PhysicsObject
{
public:
	CATFOOD_GENERATED("Pickups");

	virtual void Begin() override;
};