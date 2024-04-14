#include "MenuObject.h"
#include <UI/MenuUI.h>

void MenuObject::Begin()
{
	Cam = new CameraComponent();
	Attach(Cam);
	Cam->Use();

	UICanvas::CreateNewCanvas<MenuUI>();
}
