#include "GuiSlider.h"
#include "App.h"
#include "GuiManager.h"

GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, SDL_Rect Thumb) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;
	texture = app->guiManager->UItexture;
	canClick = true;
	drawBasic = false;
}

GuiSlider::~GuiSlider()
{
}

bool GuiSlider::Update(float dt)
{
	return true;
}

bool GuiSlider::Draw(Render* render)
{
	return true;
}
