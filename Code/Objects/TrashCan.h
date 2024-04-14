#pragma once
#include <GENERATED/TrashCan.h>
#include <Objects/WorldObject.h>
#include <Interfaces/Interactable.h>

class TrashCan : public WorldObject, public Interactable
{
public:
	static bool TrashExists;

	TRASHCAN_GENERATED("Game");
	void Begin() override;

	void OnInteract() override;

	std::string RequiredItem;

	std::vector<std::string> QuestItems;
};