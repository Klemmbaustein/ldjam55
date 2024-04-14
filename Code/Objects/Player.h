#pragma once
#include <GENERATED/Player.h>
#include <Objects/WorldObject.h>
#include <Objects/Components/MoveComponent.h>
#include <Objects/Components/CameraComponent.h>
#include <Objects/Components/MeshComponent.h>
#include <Interfaces/Interactable.h>

class Player : public WorldObject
{
public:
	bool Active = true;

	MeshComponent* HeldMesh = new MeshComponent();
	CameraComponent* PlayerCamera = new CameraComponent();
	MoveComponent* Movement = new MoveComponent();

	Interactable* HoveredObject = nullptr;

	uint32_t HeldObjectTypeID = 0;
	std::string HeldName = "";
	std::string HeldMeshName;
	Vector3 HeldScale;

	PLAYER_GENERATED("");

	void Begin() override;
	void Update() override;
	void Destroy() override;

	void UpdateInput();
	void DropItem();
	void ClearHeldItem();

	static Player* CurrentPlayer;

	static float GameTime;
	static int CurrentDay;
};