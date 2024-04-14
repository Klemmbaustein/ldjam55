#include "ItemDispenser.h"
#include <Objects/Player.h>
#include <Objects/Components/CollisionComponent.h>
#include <Objects/Components/MeshComponent.h>
#include <Objects/Pickups/Milk.h>
#include <Objects/Pickups/Magazine.h>
#include <Sounds.h>

void ItemDispenser::Begin()
{
	AddEditorProperty(Property("Type", NativeType::Int, &Type));

	OnPropertySet();
}

void ItemDispenser::OnInteract()
{
	if (Player::CurrentPlayer->HeldObjectTypeID)
	{
		Player::CurrentPlayer->DropItem();
	}

	switch (Type)
	{
	case 0:
		Player::CurrentPlayer->HeldObjectTypeID = Magazine::GetID();
		Player::CurrentPlayer->HeldName = "Magazine";
		break;
	case 1:
		Player::CurrentPlayer->HeldObjectTypeID = Milk::GetID();
		Player::CurrentPlayer->HeldName = "Milk";
		break;
	default:
		break;
	}
	Sound::PlaySound2D(Sounds::SoundBuffers["PickUp"]);
}

void ItemDispenser::OnPropertySet()
{
	while (Components.size())
	{
		Detach(Components[0]);
	}

	ModelGenerator::ModelData m;
	std::string Name;
	switch (Type)
	{
	case 0:
		m.LoadModelFromFile("ShopRack");
		Name = "Magazine";
		break;
	case 1:
		m.LoadModelFromFile("Fridge");
		Name = "Milk";
		break;
	default:
		break;
	}
	InteractString = "Pick up " + Name;

	auto Mesh = new MeshComponent();
	Attach(Mesh);
	Mesh->Load(m);
	Mesh->RelativeTransform.Scale = 0.4f;

	auto Collide = new CollisionComponent();
	Attach(Collide);
	Collide->Load(m);
	Collide->RelativeTransform.Scale = 0.4f;
}
