#pragma once
#include <GENERATED/MenuObject.h>
#include <Objects/MenuObject.h>
#include <Objects/Components/CameraComponent.h>

class MenuObject : public WorldObject
{
public:
	CameraComponent* Cam;

	MENUOBJECT_GENERATED("Menu");

	void Begin() override;
};