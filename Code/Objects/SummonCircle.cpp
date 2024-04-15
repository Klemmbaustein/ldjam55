#include "SummonCircle.h"
#include <Objects/Components/MeshComponent.h>
#include <Objects/Components/PointLightComponent.h>
#include <Objects/Components/PhysicsComponent.h>
#include <Objects/Player.h>
#include <UI/GameUI.h>
#include <UI/EndScreen.h>
#include <Rendering/Camera/CameraShake.h>
#include <Sounds.h>
SummonCircle* SummonCircle::Current = nullptr;

void SummonCircle::Begin()
{
	auto CircleMesh = new MeshComponent();
	Attach(CircleMesh);
	CircleMesh->Load("SummonCircle");
	CircleMesh->RelativeTransform.Scale = 2.5f;

	auto Light = new PointLightComponent();
	Attach(Light);
	Light->SetIntensity(0.75f);
	Light->SetFalloff(5);
	Light->RelativeTransform.Position.Y = 3;

	auto Collider = new PhysicsComponent();
	Attach(Collider);
	Collider->CreateBox(Transform(0, 0, Vector3(5, 0.1f, 5)), Physics::MotionType::Static, Physics::Layer::Static);

	InteractString = "Sacrifice item";
	Current = this;

#if !EDITOR
	switch (Player::CurrentDay)
	{
	case 0:
		QuestItems =
		{
			"Magazine",
			"Drill",
		};
		break;
	case 1:
		QuestItems =
		{
			"Milk",
			"Barrel",
		};
		break;
	case 2:
		QuestItems =
		{
			"Magazine",
			"Wood Plank",
			"Barrel",
			"Milk",
		};
	case 3:
		QuestItems =
		{
			"Milk",
			"Magazine",
			"Drill",
			"Barrel",
			"Milk",
		};
		break;
	case 4:
		QuestItems =
		{
			"Magazine",
			"Wood Plank",
			"Drill",
			"Magazine",
			"Milk",
			"Barrel",
		};
		break;
	case 5:
		QuestItems =
		{
			"Magazine",
			"Barrel",
			"Wood Plank",
			"Magazine",
			"Drill",
			"Human",
		};
		break;
	default:
		break;
	}
	if (QuestItems.size())
	{
		RequiredItem = QuestItems.at(0);
	}

	GameUI::CurrentUI->GenerateTaskList();
#endif
}

void SummonCircle::Destroy()
{
	Current = nullptr;
}

void SummonCircle::OnInteract()
{
	if (Player::CurrentPlayer->HeldName != RequiredItem || !Player::CurrentPlayer->HeldObjectTypeID)
	{
		GameUI::CurrentUI->DisplayMessage("Requires " + RequiredItem, Vector3(1, 0.2f, 0.1f));
		return;
	}
	GameUI::CurrentUI->DisplayMessage(RequiredItem + " sacrificed", Vector3(1, 0.2f, 1));
	QuestItems.erase(QuestItems.begin());
	if (QuestItems.size())
	{
		GameUI::CurrentUI->DisplayMessage(std::to_string(QuestItems.size()) + " more item(s) required", Vector3(1, 1, 0.1f));
		RequiredItem = QuestItems[0];
		GameUI::CurrentUI->GenerateTaskList();
	}
	else
	{
		GameUI::CurrentUI->DisplayMessage("All required items sacrificed", Vector3(1, 0.2f, 1));
		RequiredItem.clear();
		CanInteract = false;
		InteractString = "No more items required";
		GameUI::TaskComplete();
	}
	Player::CurrentPlayer->HeldObjectTypeID = 0;
	CameraShake::PlayDefaultCameraShake(0.6f);
	Sound::PlaySound2D(Sounds::SoundBuffers["Hit2"]);
	Player::CurrentPlayer->ClearHeldItem();
	if (Player::CurrentDay > 0)
	{
		GameUI::CurrentUI->DisplayMessage("+1 second", Vector3(1, 0.2f, 1));
		Player::GameTime += 1;
	}
}
