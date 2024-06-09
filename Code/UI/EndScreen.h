#pragma once
#include <UI/UICanvas.h>
#include <UI/UIBackground.h>

class EndScreen : public UICanvas
{
public:
	float Time = 0;

	UIBackground* Background = new UIBackground(UIBox::Orientation::Vertical, -1, Vector3(0.01f, 0, 0.05f), 2);

	EndScreen();

	void Tick();

	void GenerateScreen();
};