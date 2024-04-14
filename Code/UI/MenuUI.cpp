#include "MenuUI.h"
#include <UI/UIButton.h>
#include <Engine/Input.h>
#include <Engine/Subsystem/Scene.h>
#include <Engine/Application.h>
#include <Engine/Subsystem/Sound.h>

MenuUI::MenuUI()
{
	Font = new TextRenderer("Font.ttf");
	
	(new UIBox(UIBox::Orientation::Vertical, Vector2(-0.9f, -0.7f)))
		->AddChild((new UIButton(UIBox::Orientation::Vertical, 0, 0, this, 0))
			->SetMinSize(Vector2(0.5f, 0))
			->AddChild((new UIText(1, 1, "New Game", Font))
				->SetPadding(0.05f)))
		->AddChild((new UIButton(UIBox::Orientation::Vertical, 0, 0, this, 2))
			->SetMinSize(Vector2(0.5f, 0))
			->AddChild((new UIText(1, 1, "Full Screen", Font))
				->SetPadding(0.05f)))
		->AddChild((new UIButton(UIBox::Orientation::Vertical, 0, 0, this, 3))
			->SetMinSize(Vector2(0.5f, 0))
			->AddChild((new UIText(1, 1, "Quit", Font))
				->SetPadding(0.05f)));

	VolumeField = new UITextField(Vector2(0), 0, this, 4, Font);

	(new UIBox(UIBox::Orientation::Vertical, 0))
		->SetPosition(Vector2(0.7f, -0.7f))
		->AddChild(new UIText(1, 1, "Volume %", Font))
		->AddChild(VolumeField
			->SetTextSize(0.8f)
			->SetText("100")
			->SetMinSize(Vector2(0.3f, 0.1f)));

	Input::CursorVisible = true;
}

MenuUI::~MenuUI()
{
	delete Font;
}

void MenuUI::SaveSettings()
{
}

void MenuUI::OnButtonClicked(int Index)
{
	switch (Index)
	{
	case 0:
		Scene::LoadNewScene("MainScene");
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
	default:
		break;
	}
}
