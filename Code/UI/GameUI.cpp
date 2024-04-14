#include "GameUI.h"
#include <Objects/Player.h>
#include <UI/UIBackground.h>
#include <Objects/SummonCircle.h>
#include <Objects/Dirt.h>
#include <Objects/Customer.h>
#include <Objects/TrashCan.h>
#include "EndScreen.h"
#include <Engine/Log.h>
#include <Sounds.h>
GameUI* GameUI::CurrentUI = nullptr;
TextRenderer* GameUI::GameFont = nullptr;
bool GameUI::HasTasks = true;

void GameUI::AddTask(std::string Name, Vector3 Color)
{
	TaskList->AddChild(new UIText(0.7f, Color, "- " + Name, GameFont));

}

std::string GameUI::GetDayString(int Day)
{
	switch (Day)
	{
	case 0:
		return "Sunday";
	case 1:
		return "Monday";
	case 2:
		return "Tuesday";
	case 3:
		return "Wednesday";
	case 4:
		return "Thursday";
	case 5:
		return "Friday";
	default:
		break;
	}
	return std::string();
}

GameUI::GameUI()
{
	if (!GameFont)
	{
		GameFont = new TextRenderer("Miracode.ttf");
	}

	InteractText = new UIText(0.75f, Vector3(0.8f, 1, 0.7f), "", GameFont);
	HoldText = new UIText(0.75f, 0.8f, "", GameFont);
	DayText = new UIText(0.75f, 0.8f, "", GameFont);

	(new UIBox(UIBox::Orientation::Horizontal, -1))
		->SetMinSize(2)
		->SetVerticalAlign(UIBox::Align::Centered)
		->SetHorizontalAlign(UIBox::Align::Centered)
		->AddChild((new UIBackground(UIBox::Orientation::Horizontal, 0, 1, 0.1f))
			->SetUseTexture(true, "Crosshair")
			->SetSizeMode(UIBox::SizeMode::PixelRelative));
	(new UIBox(UIBox::Orientation::Horizontal, Vector2(-1, -0.2f)))
		->SetVerticalAlign(UIBox::Align::Centered)
		->SetHorizontalAlign(UIBox::Align::Centered)
		->SetMinSize(Vector2(2, 0.1f))
		->AddChild(InteractText);

	(new UIBox(UIBox::Orientation::Horizontal, Vector2(-1, -0.3f)))
		->SetVerticalAlign(UIBox::Align::Centered)
		->SetHorizontalAlign(UIBox::Align::Centered)
		->SetMinSize(Vector2(2, 0.1f))
		->AddChild(HoldText);

	MessageBox = new UIBox(UIBox::Orientation::Vertical, 0);

	(new UIBox(UIBox::Orientation::Vertical, Vector2(-0.5f, 0.3f)))
		->SetMinSize(Vector2(1, 0.5f))
		->SetVerticalAlign(UIBox::Align::Default)
		->AddChild(MessageBox
			->SetHorizontalAlign(UIBox::Align::Centered)
			->SetPadding(0.05f)
			->SetMinSize(Vector2(0.9f, 0)));

	TaskList = new UIBox(UIBox::Orientation::Vertical, 0);

	(new UIBox(UIBox::Orientation::Vertical, Vector2(0.5f)))
		->SetMinSize(Vector2(0.5f, 0.47f))
		->AddChild(new UIText(0.75f, 1, "Task List:", GameFont))
		->AddChild(TaskList);

	(new UIBox(UIBox::Orientation::Horizontal, Vector2(-1, 0.9f)))
		->SetMinSize(Vector2(2, 0.1f))
		->SetHorizontalAlign(UIBox::Align::Centered)
		->SetVerticalAlign(UIBox::Align::Centered)
		->AddChild(DayText);

	if (Player::CurrentDay != 0)
	{
		CustomerText = new UIText(0.75f, 1.0f, "", GameFont);
		CustomerBar = new UIBackground(UIBox::Orientation::Horizontal, 0, 1, 0);

		(new UIBackground(UIBox::Orientation::Vertical, Vector2(-0.95f), 0, Vector2(0.5f, 0.15f)))
			->SetOpacity(0.9f)
			->AddChild(CustomerText
				->SetPadding(0.05f))
			->AddChild(CustomerBar
				->SetBorder(UIBox::BorderType::Rounded, 0.5f));
	}

	CurrentUI = this;
	HasTasks = true;
	GenerateTaskList();
}

void GameUI::Tick()
{
	auto p = Player::CurrentPlayer;
	if (p->HoveredObject)
	{
		std::string str = p->HoveredObject->InteractString;

		if (p->HoveredObject->CanInteract)
		{
			str = "[Left Mouse Button]: " + str;
		}

		if (InteractText->GetText() != str)
		{
			InteractText->GetParent()->RedrawElement();
		}
		InteractText->SetText(str);
	}
	else
	{
		if (!InteractText->GetText().empty())
		{
			InteractText->GetParent()->RedrawElement();
		}
		InteractText->SetText("");
	}

	if (p->HeldObjectTypeID != 0)
	{
		std::string str = "Holding " + p->HeldName + " (Right Mouse Button to throw)";
		if (HoldText->GetText() != str)
		{
			HoldText->GetParent()->RedrawElement();
		}
		HoldText->SetText(str);
	}
	else
	{
		if (!HoldText->GetText().empty())
		{
			HoldText->GetParent()->RedrawElement();
		}
		HoldText->SetText("");
	}
	if (Player::CurrentDay != 0 && Customer::Current)
	{
		std::string Seconds = std::to_string(int(Player::GameTime) % 60);
		if (Seconds.size() == 1)
		{
			Seconds = "0" + Seconds;
		}

		std::string str = GetDayString(Player::CurrentDay) + " : " + std::to_string(int(Player::GameTime) / 60) + ":" + Seconds;
		if (DayText->GetText() != str)
		{
			DayText->GetParent()->RedrawElement();
		}
		DayText->SetText(str);

		CustomerText->SetText("Customer");

		float Percentage = Customer::Current->Timer / 22;
		CustomerBar->SetMinSize(Vector2(Percentage / 2.25f, 0.075f));
		CustomerBar->SetColor(Vector3::Lerp(Vector3(1, 0, 0), Vector3(0, 1, 0), Percentage));

		std::string CustomerString = Customer::Current->Timer > 0 ? "Customer waiting" : "No customer";
		if (CustomerText->GetText() != CustomerString)
		{
			CustomerText->GetParent()->RedrawElement();
		}
		CustomerText->SetText(CustomerString);
	}
	else
	{
		DayText->SetText(GetDayString(Player::CurrentDay) + " : --:--");
	}

	if (MessageTimer > 0)
	{
		MessageTimer -= Performance::DeltaTime;
		if (MessageTimer <= 0)
		{
			MessageBox->DeleteChildren();
			MessageBox->GetParent()->RedrawElement();
		}
	}
}

void GameUI::DisplayMessage(std::string Message, Vector3 Color)
{
	Log::Print("Display message: " + Message);
	MessageTimer = 6;

	MessageBox->AddChild(new UIText(0.75f, Color, Message, GameFont));
	MessageBox->GetParent()->RedrawElement();
	//if (Player::CurrentDay == 0)
	//UICanvas::CreateNewCanvas<EndScreen>();
}

void GameUI::GenerateTaskList()
{
	TaskList->DeleteChildren();

	if (SummonCircle::Current && !SummonCircle::Current->RequiredItem.empty())
	{
		AddTask("Sacrifice " + SummonCircle::Current->RequiredItem, Vector3(1, 0.2f, 1));
	}
	if (!Dirt::CleanedAll)
	{
		AddTask("Clean shop", 1);
	}

	if (TrashCan::TrashExists)
	{
		AddTask("Throw away trash", 1);
	}

	if (Player::CurrentDay != 0 && Player::GameTime > 0)
	{
		AddTask("Serve customers", 1);
	}

	if (TaskList->GetChildren().empty() && Player::CurrentPlayer->Active)
	{
		DisplayMessage("All tasks completed", Vector3(0.2f, 1, 0));
		AddTask("No tasks", 1);
		HasTasks = false;
		if (Player::CurrentDay == 0)
		{
			Player::CurrentPlayer->Active = false;
			CreateNewCanvas<EndScreen>();
		}
	}

	TaskList->GetParent()->RedrawElement();
}

void GameUI::TaskComplete()
{
	CurrentUI->DisplayMessage("Task completed", Vector3(0.3f, 1, 0.2f));
	CurrentUI->GenerateTaskList();
	Sound::PlaySound2D(Sounds::SoundBuffers["Task"]);
}
