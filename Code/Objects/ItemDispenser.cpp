#include "ItemDispenser.h"
#include <Objects/Player.h>
#include <Objects/Components/CollisionComponent.h>
#include <Objects/Components/MeshComponent.h>
#include <Objects/Pickups/Milk.h>
#include <Objects/Pickups/Magazine.h>
#include <Sounds.h>
#include <Objects/Pickups/CatFood.h>

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
		Player::CurrentPlayer->HeldMeshName = "Magazine";
		Player::CurrentPlayer->HeldScale = 0.25f;
		break;
	case 1:
		Player::CurrentPlayer->HeldObjectTypeID = Milk::GetID();
		Player::CurrentPlayer->HeldName = "Milk";
		Player::CurrentPlayer->HeldMeshName = "Milk";
		Player::CurrentPlayer->HeldScale = 0.25f;
		break;
	case 2:
		Player::CurrentPlayer->HeldObjectTypeID = CatFood::GetID();
		Player::CurrentPlayer->HeldName = "Cat Food";
		Player::CurrentPlayer->HeldMeshName = "AnimalFood";
		Player::CurrentPlayer->HeldScale = 0.15f;
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
	case 2:
		m.LoadModelFromFile("AnimalFoodStand");
		Name = "Cat Food";
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
