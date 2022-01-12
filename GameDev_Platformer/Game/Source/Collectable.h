#pragma once
#include "Entity.h"
class Collectable :   public Entity
{
public:
	Collectable(iPoint pos);
protected:
	SDL_Rect r;
};

