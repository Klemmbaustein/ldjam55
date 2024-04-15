#include "IntroScreen.h"
#include <UI/UIBackground.h>
#include <Engine/Input.h>
#include <Engine/Subsystem/Scene.h>

IntroScreen::IntroScreen()
{
	IntroFont = new TextRenderer("Miracode.ttf");

	(new UIBackground(UIBox::Orientation::Vertical, -1, Vector3(0.01f, 0, 0.07f), 2))
		->SetVerticalAlign(UIBox::Align::Centered)
		->SetHorizontalAlign(UIBox::Align::Centered)
		->AddChild((new UIBox(UIBox::Orientation::Vertical, 0))
			->AddChild(new UIText(0.7f, 0.7f, "You are dying of a rare deadly illness. There is no known cure.", IntroFont))
			->AddChild(new UIText(0.7f, 0.7f, "You heard a demon summoning ritual could cure it.", IntroFont))
			->AddChild(new UIText(0.7f, 0.7f, "Because there aren't any other options for you, you decide to try it.", IntroFont))
			->AddChild(new UIText(0.7f, 0.7f, "The place that fits all the conditions for the ritual is the shop you work at.", IntroFont))
			->AddChild(new UIText(0.7f, 1.0f, "Press the left mouse button to continue.", IntroFont))
		);

	UIBox::RedrawUI();
}

IntroScreen::~IntroScreen()
{
}

void IntroScreen::Tick()
{
	if (Input::IsLMBClicked)
	{
		Scene::LoadNewScene("MainScene");
	}
}
