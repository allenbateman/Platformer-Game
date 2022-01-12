#include "Collectable.h"
Collectable::Collectable(iPoint pos) : Entity(pos)
{
	position.x = pos.x;
	position.y = pos.y;
}