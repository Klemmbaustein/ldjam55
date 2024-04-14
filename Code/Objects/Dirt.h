#pragma once
#include <GENERATED/Dirt.h>
#include <Objects/WorldObject.h>
#include <Interfaces/Interactable.h>

class Dirt : public WorldObject, public Interactable
{
public:
	static bool CleanedAll;
	DIRT_GENERATED("Game");

	void Begin() override;
	void OnInteract() override;
	void Update() override;
};