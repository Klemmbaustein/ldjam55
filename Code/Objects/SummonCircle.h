#pragma once
#include <GENERATED/SummonCircle.h>
#include <Objects/WorldObject.h>
#include <Interfaces/Interactable.h>

class SummonCircle : public WorldObject, public Interactable
{
public:
	SUMMONCIRCLE_GENERATED("Game");
	void Begin() override;
	void Destroy() override;

	void OnInteract() override;

	static SummonCircle* Current;

	std::string RequiredItem;

	std::vector<std::string> QuestItems;
};