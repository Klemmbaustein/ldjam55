#include "Dirt.h"
#include <Objects/Components/MeshComponent.h>
#include <Objects/Components/PhysicsComponent.h>
#include <Objects/Player.h>
#include <Objects/Pickups/Broom.h>
#include <Objects/Pickups/TrashBag.h>
#include <UI/GameUI.h>
#include <Sounds.h>

bool Dirt::CleanedAll = false;

void Dirt::Begin()
{
	CleanedAll = false;
	auto CircleMesh = new MeshComponent();
	Attach(CircleMesh);
	CircleMesh->Load("Dirt");
	CircleMesh->RelativeTransform.Scale = 0.5f;

	auto Collider = new PhysicsComponent();
	Attach(Collider);
	Collider->CreateBox(Transform(0, 0, Vector3(1, 0.1f, 1)), Physics::MotionType::Static, Physics::Layer::Static);

}

void Dirt::OnInteract()
{
	Sound::PlaySound2D(Sounds::SoundBuffers["Broom"]);
	// If only this object remains, all dirt has been cleaned up.
	CleanedAll = Objects::GetAllObjectsWithID(Dirt::GetID()).size() == 1;
	Objects::DestroyObject(this);

	if (CleanedAll)
	{
		GameUI::CurrentUI->TaskComplete();
	}
	Objects::SpawnObject<TrashBag>(GetTransform() + Transform(Vector3(0, 1, 0), 0, 1));
}

void Dirt::Update()
{
#if EDITOR
	return;
#endif

	if (Player::CurrentPlayer->HeldObjectTypeID == Broom::GetID())
	{
		InteractString = "Clean";
		CanInteract = true;
	}
	else
	{
		InteractString = "Requires broom";
		CanInteract = false;
	}
}
