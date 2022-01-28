#include "GuiSlider.h"
#include "App.h"
#include "GuiManager.h"
#include "Log.h"

GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, SDL_Rect Thumb) : GuiControl(GuiControlType::SLIDER, id)
{
	this->bounds = bounds;
	this->text = text;
	this->thumbRect = Thumb;
	texture = app->guiManager->UItexture;
	canClick = true;
	drawBasic = false;
}

GuiSlider::~GuiSlider()
{
}

bool GuiSlider::Update(float dt)
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

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				if (mouseX < bounds.x)
					thumbRect.x = bounds.x + thumbRect.w;

				if (mouseX > (bounds.x + bounds.w))
					thumbRect.x = bounds.x - thumbRect.w;

				thumbRect.x = mouseX;

				value = GetValue(mouseX);
				LOG("slider value:%f", GetValue(mouseX));
				state = GuiControlState::PRESSED;
			}

			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				NotifyObserver();
			}
		}else state = GuiControlState::NORMAL;
	}

	return false;
}

bool GuiSlider::Draw(Render* render)
{


	switch (state)
	{

	case GuiControlState::DISABLED:
	{
		render->DrawRectangle(bounds, 125, 200, 0, 0);
		render->DrawRectangle(thumbRect, 125, 200, 0, 0);



		//if (texture != NULL)
		//	render->DrawTexture(texture, bounds.x, bounds.y, &disabledRec);
	} break;

	case GuiControlState::NORMAL:
	{
		render->DrawRectangle(bounds, 125, 125, 0, 125);
		render->DrawRectangle(thumbRect, 0, 200, 0, 255);
		//if (texture != NULL)
		//	render->DrawTexture(texture, bounds.x, bounds.y, &normalRec);
	} break;
	case GuiControlState::FOCUSED:
	{
		render->DrawRectangle(bounds, 255, 255, 255, 160);
		render->DrawRectangle(thumbRect, 0, 255, 255, 255);
		//if (texture != NULL)
		//	render->DrawTexture(texture, bounds.x, bounds.y, &focusedRec);
	} break;
	case GuiControlState::PRESSED:
	{
		render->DrawRectangle(bounds, 255, 255, 255, 255);
		render->DrawRectangle(thumbRect, 0, 255, 255, 255);
		//if (texture != NULL)
		//	render->DrawTexture(texture, bounds.x, bounds.y, &pressedRec);

	} break;

	case GuiControlState::SELECTED:
	{
		render->DrawRectangle(bounds, 0, 255, 0, 255);
		render->DrawRectangle(thumbRect, 0, 255, 255, 255);
		//if (texture != NULL)
		//	render->DrawTexture(texture, bounds.x, bounds.y, &selectedRec);
	}break;

	default:
		break;
	}
	return true;
}

int GuiSlider::GetValue(float pos)
{

	if (pos < bounds.x)
		return value = 0;

	if (pos > (bounds.x + bounds.w))
		return	value = 100;

	value = 0 + (100 - 0) * ((pos - bounds.x) / ((bounds.x + bounds.w) - bounds.x));

	return value;
}
