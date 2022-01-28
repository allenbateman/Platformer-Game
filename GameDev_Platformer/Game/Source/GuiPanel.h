#pragma once
#include "GuiManager.h"
class GuiPanel : public GuiManager
{

	GuiPanel(uint32 id, SDL_Rect bounds, const char* text, int fontid);
};

