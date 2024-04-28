#include "Player.h"
#include <Engine/Input.h>
#include <UI/GameUI.h>
#include <Math/Physics/Physics.h>
#include <Objects/PhysicsObject.h>
#include <Engine/Log.h>
#include <Engine/EngineError.h>
#include <Engine/EngineRandom.h>
#include <UI/EndScreen.h>
#include <algorithm> 
#include <Sounds.h>
#include <Objects/MeshObject.h>
#include <Engine/Subsystem/Scene.h>
#include "Customer.h"
#include "TrashCan.h"

Player* Player::CurrentPlayer = nullptr;
float Player::GameTime = INFINITY;
int Player::CurrentDay = 0;
bool FirstFrame = false;

void Player::Begin()
{
	GameTime = 2 * 60;
	Attach(PlayerCamera);
	PlayerCamera->RelativeTransform.Position.Y = 1.5f;
	PlayerCamera->Use();

	Attach(Movement);
	Movement->CollideStatic = false;

	Attach(HeldMesh);

	CurrentPlayer = this;

	UICanvas::CreateNewCanvas<GameUI>();

#if !EDITOR
	if (CurrentDay == 0)
	{
		GameUI::CurrentUI->DisplayMessage("Time limit is disabled for the day", 1);
	}
	FirstFrame = true;
#endif
}

bool EscDown = false;

void Player::Update()
{
#if EDITOR
	return;
#endif

	if (CurrentDay == 5 && FirstFrame)
	{
		auto Obj = Objects::GetAllObjectsWithID(MeshObject::GetID());

		for (auto& i : Obj)
		{
			if (i->Name == "Skybox")
			{
				auto m = static_cast<MeshObject*>(i);
				m->MaterialNames.clear();
				m->LoadFromFile("GameEndSky");
			}
		}
	}
	FirstFrame = false;

	Input::CursorVisible = false;
	if (!Active)
	{
		HoveredObject = nullptr;
		DropItem();
		return;
	}


	if (Input::IsKeyDown(Input::Key::ESCAPE))
	{
		if (!EscDown)
		{
			if (Stats::TimeMultiplier == 0)
			{
				Stats::TimeMultiplier = 1;
				GameUI::CurrentUI->DisplayMessage("Game resumed.", 1);
			}
			else
			{
				Stats::TimeMultiplier = 0;
				GameUI::CurrentUI->DisplayMessage("Game paused. Press X to open the main menu", 1);
			}
		}
		EscDown = true;
	}
	else
	{
		EscDown = false;
	}

	if (Input::IsKeyDown(Input::Key::x) && Stats::TimeMultiplier == 0)
	{
		Scene::LoadNewScene("Menu");
	}

	if (CurrentDay != 0)
	{
		if (GameTime > 20 && GameTime - Stats::DeltaTime <= 20)
		{
			GameUI::CurrentUI->DisplayMessage("20 seconds remaining!", Vector3(1, 0, 0));
		}

		if (GameTime > 0)
		{
			if (!Customer::Current && !TrashCan::TrashExists)
			{
				GameTime -= Stats::DeltaTime * 4;
			}
			GameTime -= Stats::DeltaTime;
		}
		if (GameTime <= 0)
		{
			GameUI::TaskComplete();
			GameUI::CurrentUI->DisplayMessage("Time over!", Vector3(1, 0, 0));
			Active = false;
			UICanvas::CreateNewCanvas<EndScreen>();
		}
	}

	if (Stats::TimeMultiplier == 0)
	{
		return;
	}

	UpdateInput();

	Vector3 Pos = PlayerCamera->GetWorldTransform().Position;
	auto Hit = Physics::RayCast(Pos, Pos + Vector3::GetForwardVector(PlayerCamera->RelativeTransform.Rotation) * 15, Physics::Layer::Static, { this });
	if (Hit.Hit)
	{
		HoveredObject = dynamic_cast<Interactable*>(Hit.HitComponent->GetParent());
	}
	else
	{
		HoveredObject = nullptr;
	}

	if (Input::IsLMBClicked && HoveredObject && HoveredObject->CanInteract)
	{
		HoveredObject->OnInteract();
		// Avoid problems if the object is destroyed.
		HoveredObject = nullptr;
	}

	if (Input::IsRMBClicked && HeldName != "Human")
	{
		DropItem();
	}

	if ((!HeldMesh->GetModel() || HeldMesh->GetModel()->Meshes.empty()) && HeldObjectTypeID)
	{
		HeldMesh->Load(HeldMeshName);
		HeldMesh->RelativeTransform.Scale = HeldScale;
	}
	HeldMesh->RelativeTransform.Position = Vector3::GetForwardVector(PlayerCamera->RelativeTransform.Rotation) * 1.5f
		+ Vector3::GetRightVector(PlayerCamera->RelativeTransform.Rotation);
	HeldMesh->RelativeTransform.Rotation.Y = -PlayerCamera->RelativeTransform.Rotation.Y;
}

void Player::Destroy()
{
	if (CurrentPlayer == this)
	{
		CurrentPlayer = nullptr;
	}
}

void Player::UpdateInput()
{
	PlayerCamera->RelativeTransform.Rotation += Vector3(Input::MouseMovement.Y, Input::MouseMovement.X, 0);
	PlayerCamera->RelativeTransform.Rotation.X = std::clamp(PlayerCamera->RelativeTransform.Rotation.X, -90.0f, 90.0f);

	Vector3 CameraRotation = Vector3(0, PlayerCamera->RelativeTransform.Rotation.Y, 0);

	if (Input::IsKeyDown(Input::Key::w))
	{
		Movement->AddMovementInput(Vector3::GetForwardVector(CameraRotation));
	}
	if (Input::IsKeyDown(Input::Key::s))
	{
		Movement->AddMovementInput(-Vector3::GetForwardVector(CameraRotation));
	}

	if (Input::IsKeyDown(Input::Key::d))
	{
		Movement->AddMovementInput(Vector3::GetRightVector(CameraRotation));
	}
	if (Input::IsKeyDown(Input::Key::a))
	{
		Movement->AddMovementInput(-Vector3::GetRightVector(CameraRotation));
	}
}

void Player::DropItem()
{
	if (HeldObjectTypeID == 0)
	{
		return;
	}

	Transform SpawnTransform = GetTransform();
	Vector3 CameraRotation = Vector3(0, PlayerCamera->RelativeTransform.Rotation.Y, 0);
	SpawnTransform.Position += Vector3::GetForwardVector(CameraRotation);

	PhysicsObject* Obj = dynamic_cast<PhysicsObject*>(Objects::SpawnObjectFromID(HeldObjectTypeID, SpawnTransform));

	Obj->Body->SetVelocity(Vector3::GetForwardVector(PlayerCamera->RelativeTransform.Rotation) * 8);
	Obj->Body->SetAngularVelocity(Vector3(Random::GetRandomFloat(-400, 400), Random::GetRandomFloat(-400, 400), Random::GetRandomFloat(-400, 400)));
	HeldObjectTypeID = 0;
	Sound::PlaySound2D(Sounds::SoundBuffers["Throw"], 1, 0.5f);
	ClearHeldItem();
}

void Player::ClearHeldItem()
{
	HeldMesh->Load(ModelGenerator::ModelData());
}
