#include "PhysicsObject.h"
#include "Player.h"
#include <Sounds.h>

void PhysicsObject::Begin()
{
}

void PhysicsObject::Update()
{
	Transform t = GetTransform();
	t.Position = 0;
#if EDITOR
	t.Rotation = Vector3(t.Rotation.Z, t.Rotation.Y, t.Rotation.X).DegreesToRadians();
#else
	t.Rotation = Vector3(t.Rotation.Z, t.Rotation.Y, t.Rotation.X).DegreesToRadians();
#endif

#if !EDITOR
	SetTransform(Body->GetBodyWorldTransform());
#else
	Body->SetPosition(GetTransform().Position + Vector3::TranslateVector(MeshOffset, t));
	Body->SetRotation(GetTransform().Rotation);
#endif
}

void PhysicsObject::OnInteract()
{
	Sound::PlaySound2D(Sounds::SoundBuffers["PickUp"]);
	Player::CurrentPlayer->DropItem();
	Player::CurrentPlayer->HeldName = PickupName;
	Player::CurrentPlayer->HeldObjectTypeID = TypeID;
	Player::CurrentPlayer->HeldMeshName = MeshName;
	Player::CurrentPlayer->HeldScale = MeshScale;
	Objects::DestroyObject(this);
}

void PhysicsObject::CreateObject(std::string MeshName, Transform ColliderTransform)
{
	this->MeshName = MeshName;
	MeshScale = ColliderTransform.Scale;

	Attach(ObjectMesh);
	ObjectMesh->Load(MeshName);
	ObjectMesh->RelativeTransform = ColliderTransform;

	MeshOffset = ObjectMesh->GetBoundingBox().center * ColliderTransform.Scale;
	ObjectMesh->RelativeTransform.Position = -Vector3(0, MeshOffset.Y, 0);

	Attach(Body);
	ColliderTransform.Scale = ObjectMesh->GetBoundingBox().extents * ColliderTransform.Scale * 2.0f;

	Body->CreateBox(ColliderTransform, Physics::MotionType::Dynamic);
}
