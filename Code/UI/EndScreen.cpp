#include "EndScreen.h"
#include <Engine/Subsystem/Scene.h>
#include <UI/UIText.h>
#include "GameUI.h"
#include <Objects/Player.h>
#include <Engine/Input.h>
#include <Objects/TrashCan.h>
#include <cmath>
#include <Objects/Dirt.h>

EndScreen::EndScreen()
{
	Background->SetVerticalAlign(UIBox::Align::Centered);
	Background->SetHorizontalAlign(UIBox::Align::Centered);
}

void EndScreen::Tick()
{
	Background->SetOpacity(std::min(Time - 2, 1.0f));
	UIBox::RedrawUI();
	if (Time < 4)
	{
		Time += Performance::DeltaTime;
		if (Time >= 4)
		{
			GenerateScreen();
		}
	}
	else if (Input::IsLMBClicked)
	{
		if (!GameUI::HasTasks)
		{
			Player::CurrentDay++;
		}
		TrashCan::TrashExists = true;
		Dirt::CleanedAll = false;
		Scene::LoadNewScene("MainScene");
	}
}

void EndScreen::GenerateScreen()
{
	UIBox* TextBox = new UIBox(UIBox::Orientation::Vertical, 0);
	Background->AddChild(TextBox);
	if (GameUI::HasTasks)
	{
		TextBox->AddChild((new UIText(1.5f, 1, "Failed to complete all tasks", GameUI::GameFont))
			->SetPadding(0.05f));
		TextBox->AddChild((new UIText(0.75f, 0.6f, "Left mouse button to retry day", GameUI::GameFont))
			->SetPadding(0.05f));
		return;
	}
	TextBox->AddChild((new UIText(1.5f, 0.75f, GameUI::GetDayString(Player::CurrentDay) + " completed", GameUI::GameFont))
		->SetPadding(0.05f));
	TextBox->AddChild((new UIText(0.75f, 0.6f, "Finished all task in time", GameUI::GameFont))
		->SetPadding(0.05f));
	TextBox->AddChild((new UIText(1.5f, std::vector{ TextSegment("Next day: ", 0.75f), TextSegment(GameUI::GetDayString(Player::CurrentDay + 1), 1) }, GameUI::GameFont))
		->SetPadding(0.05f));
	TextBox->AddChild((new UIText(0.75f, 0.6f, "Left mouse button to continue", GameUI::GameFont))
		->SetPadding(0.05f));
}
