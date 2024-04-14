#pragma once
#include <GENERATED/Customer.h>
#include <Objects/WorldObject.h>
#include <Interfaces/Interactable.h>
#include <Objects/Components/MeshComponent.h>
#include <Objects/Components/PhysicsComponent.h>
#include <Objects/Components/ParticleComponent.h>

class Customer : public WorldObject, public Interactable
{
public:
	CUSTOMER_GENERATED("Game");
	void Begin() override;
	void Destroy() override;

	MeshComponent* Mesh = nullptr;
	PhysicsComponent* Collider = nullptr;
	ParticleComponent* Particle = nullptr;

	float Timer = -5;

	void OnInteract() override;
	void Update() override;

	static Customer* Current;


	std::string RequiredItem;
	std::string DisplayName;

	std::vector<std::string> QuestItems;
};