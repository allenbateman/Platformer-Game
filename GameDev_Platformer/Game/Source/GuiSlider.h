#pragma once
#include "GuiControl.h"
#include "Animation.h"

#include "Point.h"
#include "SString.h"

class GuiSlider : public GuiControl
{

public:

	GuiSlider(uint32 id, SDL_Rect bounds, SDL_Rect Thumb);
	virtual ~GuiSlider();

	bool Update(float dt);
	bool Draw(Render* render);
	int GetValue(float pos);

	int mouseX, mouseY;
	unsigned int click;

	int value;

	bool canClick = true;
	bool drawBasic = false;

	SDL_Rect thumbBounds;
	SDL_Rect thumbRect;
	SDL_Rect backgroundRect;
	SDL_Texture* texture;


	Animation* hoverAnim, pressedAnim;
	Animation* currentAnim;
};

