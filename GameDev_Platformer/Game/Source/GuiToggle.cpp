#include "GuiToggle.h"
#include "GuiManager.h"
#include "Render.h"
#include "ModuleFonts.h"
#include "App.h"
#include "Audio.h"

GuiToggle::GuiToggle(uint32 id, SDL_Rect bounds) : GuiControl(GuiControlType::TOGGLE, id)
{
	this->bounds = bounds;
	texture = app->guiManager->UItexture;
	canClick = true;
	drawBasic = false;
}

GuiToggle::~GuiToggle()
{
}

bool GuiToggle::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		// L14: TODO 3: Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
			(mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
		{
			state = GuiControlState::FOCUSED;

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
			{
				state = GuiControlState::PRESSED;
				State != State;
			}

			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				NotifyObserver();
			}
		}
		else state = GuiControlState::NORMAL;
	}
	return false;
}

bool GuiToggle::Draw(Render* render)
{


	switch (state)
	{

	case GuiControlState::DISABLED:
	{
		render->DrawRectangle(bounds, 125, 200, 0, 0);
		if (texture != NULL)
			render->DrawTexture(texture, bounds.x, bounds.y, &disabledRec);
	} break;

	case GuiControlState::NORMAL:
	{
		render->DrawRectangle(bounds, 125, 125, 0, 125);
		if (texture != NULL)
			render->DrawTexture(texture, bounds.x, bounds.y, &normalRec);
	} break;
	case GuiControlState::FOCUSED:
	{
		render->DrawRectangle(bounds, 255, 255, 255, 160);
		if (texture != NULL)
			render->DrawTexture(texture, bounds.x, bounds.y, &focusedRec);
	} break;
	case GuiControlState::PRESSED:
	{
		render->DrawRectangle(bounds, 255, 255, 255, 255);
		if (texture != NULL)
			render->DrawTexture(texture, bounds.x, bounds.y, &pressedRec);

	} break;

	case GuiControlState::SELECTED:
	{
		render->DrawRectangle(bounds, 0, 255, 0, 255);
		if (texture != NULL)
			render->DrawTexture(texture, bounds.x, bounds.y, &selectedRec);
	}break;

	default:
		break;
	}
	return false;
}
