#pragma once
#include <Objects/Components/MeshComponent.h>
#include <Objects/Components/PhysicsComponent.h>
#include <Interfaces/Interactable.h>
#include <Objects/WorldObject.h>
#include <GENERATED/PhysicsObject.h>

class PhysicsObject : public virtual WorldObject, public Interactable
{
public:
	PhysicsComponent* Body = new PhysicsComponent();
	MeshComponent* ObjectMesh = new MeshComponent();
	Vector3 MeshOffset;
	std::string MeshName;
	Vector3 MeshScale;
	std::string PickupName;
	PHYSICSOBJECT_GENERATED("Game");

	void Begin() override;
	void Update() override;

	void OnInteract() override;

	void CreateObject(std::string MeshName, Transform ColliderTransform);
};