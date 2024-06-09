#pragma once
#include <UI/UICanvas.h>
#include <UI/UIText.h>

class IntroScreen : public UICanvas
{
public:
	TextRenderer* IntroFont = nullptr;

	IntroScreen();
	~IntroScreen();

	void Tick() override;
};