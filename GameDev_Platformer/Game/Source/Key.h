#pragma once
#include "Collectable.h"
class Key :  public Collectable
{
	Key(iPoint pos);
	void Start();
	void Update();
	void PosUpdate();
};

