#pragma once
#include <UI/UICanvas.h>
#include <UI/UIText.h>
#include <UI/UITextField.h>

class MenuUI : public UICanvas
{
public:
	UIBox* Boxes[3];
	UIText* GraphicsText = nullptr;
	UITextField* VolumeField = nullptr;
	TextRenderer* Font = nullptr;
	MenuUI();
	~MenuUI();

	void SaveSettings();

	void OnButtonClicked(int Index) override;
};