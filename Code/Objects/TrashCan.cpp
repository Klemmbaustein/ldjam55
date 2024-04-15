#include "TrashCan.h"
#include <Objects/Player.h>
#include <UI/GameUI.h>
#include <Objects/Pickups/TrashBag.h>
#include <Sounds.h>
bool TrashCan::TrashExists = true;

void TrashCan::Begin()
{
	TrashExists = true;
	auto TrashMesh = new MeshComponent();
	Attach(TrashMesh);
	TrashMesh->Load("TrashCan");
	TrashMesh->RelativeTransform.Scale = 0.5f;

	auto Collider = new PhysicsComponent();
	Attach(Collider);
	Collider->CreateBox(Transform(0, 0, Vector3(1, 3, 1)), Physics::MotionType::Static, Physics::Layer::Static);

	InteractString = "Trash can";
}

void TrashCan::OnInteract()
{
	if (Player::CurrentPlayer->HeldObjectTypeID != TrashBag::GetID())
	{
		GameUI::CurrentUI->DisplayMessage("Throw away trash here", 1);
		return;
	}
	Player::CurrentPlayer->HeldObjectTypeID = 0;

	TrashExists = !Objects::GetAllObjectsWithID(TrashBag::GetID()).empty();
	GameUI::CurrentUI->DisplayMessage("Threw away trash bag", 1);
	Sound::PlaySound2D(Sounds::SoundBuffers["Drop"], 1, 1.5f);
	if (!TrashExists)
	{
		GameUI::TaskComplete();
	}
	Player::CurrentPlayer->ClearHeldItem();
}
