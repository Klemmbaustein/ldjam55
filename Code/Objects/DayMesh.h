#pragma once
#include <GENERATED/DayMesh.h>
#include <Objects/Components/MeshComponent.h>
#include <Objects/WorldObject.h>

class DayMesh : public WorldObject
{
public:
	DAYMESH_GENERATED("Game");

	void Begin() override;

	void OnPropertySet() override;

	std::string ModelFile;
	int StartDay = 0;
};