#include "MenuUI.h"
#include <UI/UIButton.h>
#include <Engine/Input.h>
#include <Engine/Subsystem/Scene.h>
#include <Engine/Application.h>
#include <Engine/Subsystem/Sound.h>
#include <UI/IntroScreen.h>
#include <Engine/Subsystem/Console.h>

bool FastGraphics = false;

MenuUI::MenuUI()
{
	Performance::TimeMultiplier = 1;
	Font = new TextRenderer("Font.ttf");
	
	Boxes[2] = (new UIBox(UIBox::Orientation::Vertical, Vector2(-0.9f, 0)))
		->AddChild(new UIText(2, 1, "Sacrificed", Font))
		->AddChild(new UIText(0.75f, 1, "A game made by Klemmbaustein for Ludum Dare 55", Font));

	Boxes[0] = new UIBox(UIBox::Orientation::Vertical, Vector2(-0.9f, -0.7f));
	Boxes[0]
		->AddChild((new UIButton(UIBox::Orientation::Vertical, 0, 0, this, 0))
			->SetMinSize(Vector2(0.5f, 0))
			->AddChild((new UIText(1, 1, "New Game", Font))
				->SetPadding(0.03f)))
		->AddChild((new UIButton(UIBox::Orientation::Vertical, 0, 0, this, 2))
			->SetMinSize(Vector2(0.5f, 0))
			->AddChild((new UIText(1, 1, "Full Screen", Font))
				->SetPadding(0.03f)))
		->AddChild((new UIButton(UIBox::Orientation::Vertical, 0, 0, this, 3))
			->SetMinSize(Vector2(0.5f, 0))
			->AddChild((new UIText(1, 1, "Quit", Font))
				->SetPadding(0.03f)));

	VolumeField = new UITextField(Vector2(0), 0, this, 4, Font);
	GraphicsText = new UIText(0.8f, 1, "Good", Font);

	Boxes[1] = new UIBox(UIBox::Orientation::Vertical, 0);
	Boxes[1]
		->SetPosition(Vector2(0.6f, -0.7f))
		->AddChild(new UIText(0.8f, 1, "Graphics quality", Font))
		->AddChild((new UIButton(UIBox::Orientation::Horizontal, 0, 0, this, 5))
			->AddChild(GraphicsText))
		->AddChild(new UIText(0.8f, 1, "Sound Volume %", Font))
		->AddChild(VolumeField
			->SetTextSize(0.8f)
			->SetText(std::to_string(int(Sound::SoundSystem->MasterVolume * 100)))
			->SetMinSize(Vector2(0.15f, 0.06f)));

	Input::CursorVisible = true;
}

MenuUI::~MenuUI()
{
	delete Font;
	delete Boxes[0];
	delete Boxes[1];
	delete Boxes[2];
}

void MenuUI::SaveSettings()
{
}

void MenuUI::OnButtonClicked(int Index)
{
	switch (Index)
	{
	case 0:
		UICanvas::CreateNewCanvas<IntroScreen>();
		delete this;
		break;
	case 2:
		Application::SetFullScreen(!Application::GetFullScreen());
		break;
	case 3:
		Application::Quit();
		break;
	case 4:
		try
		{
			Sound::SoundSystem->MasterVolume = std::stof(VolumeField->GetText()) / 100;
		}
		catch (std::exception&)
		{

		}
		VolumeField->SetText(std::to_string(int(Sound::SoundSystem->MasterVolume * 100)));
		break;
	case 5:
		FastGraphics = !FastGraphics;

		GraphicsText->SetText(FastGraphics ? "Fast" : "Good");

		if (FastGraphics)
		{
			Console::ExecuteConsoleCommand("ssao=0");
			Console::ExecuteConsoleCommand("shadows=0");
			Console::ExecuteConsoleCommand("bloom=0");
			Console::ExecuteConsoleCommand("aa_enabled=0");
		}
		else
		{
			Console::ExecuteConsoleCommand("ssao=1");
			Console::ExecuteConsoleCommand("shadows=1");
			Console::ExecuteConsoleCommand("bloom=1");
			Console::ExecuteConsoleCommand("aa_enabled=1");
		}
		break;
	default:
		break;
	}
}
