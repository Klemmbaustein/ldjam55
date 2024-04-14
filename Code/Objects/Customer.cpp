#include "Customer.h"
#include <Objects/Player.h>
#include <UI/GameUI.h>
#include <UI/EndScreen.h>
#include <Sounds.h>
#include <Engine/EngineRandom.h>
#include <Engine/Log.h>
Customer* Customer::Current = nullptr;

void Customer::Begin()
{
#if !EDITOR
	if (Player::CurrentDay == 0)
	{
		return;
	}
#endif

	Mesh = new MeshComponent();
	Attach(Mesh);
	Mesh->Load("Human");
	Mesh->RelativeTransform.Scale = 0.75f;

	Collider = new PhysicsComponent();
	Attach(Collider);
	Collider->CreateBox(Transform(0, 0, Vector3(1, 2, 1)), Physics::MotionType::Static, Physics::Layer::Static);
	Current = this;

	Particle = new ParticleComponent();
	Attach(Particle);
	Particle->LoadParticle("Customer");
	Particle->SetActive(false);
	Collider->SetActive(false);
	Mesh->SetVisibility(false);
}

void Customer::Destroy()
{
	Current = nullptr;
}

void Customer::OnInteract()
{
	if (Player::CurrentPlayer->HeldObjectTypeID && Player::CurrentPlayer->HeldName == RequiredItem)
	{
		Player::CurrentPlayer->HeldObjectTypeID = 0;
		Timer = -8.0f;
		Particle->SetActive(true);
		Particle->Reset();
		Collider->SetActive(false);
		Mesh->SetVisibility(false);
		Sound::PlaySound2D(Sounds::SoundBuffers["Customer"]);
		Player::CurrentPlayer->ClearHeldItem();
	}
	else
	{
		GameUI::CurrentUI->DisplayMessage("\"I want " + DisplayName + "\"", 1);
	}
}

void Customer::Update()
{
#if EDITOR
	return;
#endif

	if (Player::CurrentPlayer->CurrentDay == 0)
	{
		return;
	}
	if (!Player::CurrentPlayer->Active)
	{
		return;
	}

	if (Player::CurrentPlayer->HeldObjectTypeID && Player::CurrentPlayer->HeldName == RequiredItem)
	{
		InteractString = "Give " + RequiredItem;
	}
	else
	{
		InteractString = "Talk";
	}

	if (Timer > 0)
	{
		Timer -= Performance::DeltaTime;
		if (Timer <= 0)
		{
			GameUI::CurrentUI->DisplayMessage("Failed task: Serve customers", Vector3(1, 0, 0));
			Player::CurrentPlayer->Active = false;
			UICanvas::CreateNewCanvas<EndScreen>();
			return;
		}
	}
	else if (Timer < 0)
	{
		Timer += Performance::DeltaTime;
		if (Timer >= 0)
		{
			Particle->SetActive(true);
			Particle->Reset();
			Collider->SetActive(true);
			Mesh->SetVisibility(true);
			Timer = 20;
			int val = Random::GetRandomInt(0, 3);
			switch (val)
			{
			case 0:
				RequiredItem = "Magazine";
				DisplayName = "a Magazine";
				break;
			case 1:
			default:
				RequiredItem = "Milk";
				DisplayName = "Milk";
				break;
			case 2:
				RequiredItem = "Cat Food";
				DisplayName = "Cat Food";
				break;
			}
		}
	}
}
