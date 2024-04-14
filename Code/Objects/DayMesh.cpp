#include "DayMesh.h"
#include "Player.h"
#include <UI/GameUI.h>

void DayMesh::Begin()
{
	AddEditorProperty(Property("Start Day", NativeType::Int, &StartDay));
	AddEditorProperty(Property("Mesh", NativeType::String, &ModelFile));
}

void DayMesh::OnPropertySet()
{
#if !EDITOR
	if (StartDay > Player::CurrentDay)
	{
		return;
	}
#endif
	while (Components.size())
	{
		Detach(Components[0]);
	}

	auto Mesh = new MeshComponent();
	Attach(Mesh);
	Mesh->Load(ModelFile);

	Name = ModelFile + ": " + GameUI::GetDayString(StartDay) + "..";
}
