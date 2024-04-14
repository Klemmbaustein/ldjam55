#pragma once
#include <GENERATED/Player.h>
#include <Objects/WorldObject.h>
#include <Objects/Components/MoveComponent.h>
#include <Objects/Components/CameraComponent.h>
#include <Interfaces/Interactable.h>

class Player : public WorldObject
{
public:
	bool Active = true;

	CameraComponent* PlayerCamera = new CameraComponent();
	MoveComponent* Movement = new MoveComponent();

	Interactable* HoveredObject = nullptr;

	uint32_t HeldObjectTypeID = 0;
	std::string HeldName = "";

	PLAYER_GENERATED("");

	void Begin() override;
	void Update() override;
	void Destroy() override;

	void UpdateInput();
	void DropItem();

	static Player* CurrentPlayer;

	static float GameTime;
	static int CurrentDay;
};