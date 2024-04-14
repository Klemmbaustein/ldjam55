#pragma once
#include <UI/Default/UICanvas.h>
#include <UI/UIText.h>
#include <UI/UIBackground.h>

class GameUI : public UICanvas
{
	void AddTask(std::string Name, Vector3 Color);
public:
	static GameUI* CurrentUI;
	static bool HasTasks;

	static std::string GetDayString(int Day);

	GameUI();
	void Tick() override;

	static TextRenderer* GameFont;
	UIText* InteractText = nullptr;
	UIText* HoldText = nullptr;
	UIText* DayText = nullptr;
	UIText* CustomerText = nullptr;
	UIBackground* CustomerBar = nullptr;
	UIBox* MessageBox = nullptr;
	UIBox* TaskList = nullptr;

	float MessageTimer = 0;

	void DisplayMessage(std::string Message, Vector3 Color);

	void GenerateTaskList();

	static void TaskComplete();
};