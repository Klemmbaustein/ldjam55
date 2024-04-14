#pragma once
#include <Interfaces/Interactable.h>
#include <Objects/WorldObject.h>
#include <GENERATED/ItemDispenser.h>

class ItemDispenser : public WorldObject, public Interactable
{
public:
	ITEMDISPENSER_GENERATED("Game");

	int Type = 0;

	void Begin() override;
	void OnInteract() override;

	void OnPropertySet() override;
};