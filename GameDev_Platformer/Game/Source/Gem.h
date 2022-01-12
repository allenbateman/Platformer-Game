#pragma once
#include "Collectable.h"
class Gem : public Collectable
{
    Gem(iPoint pos);

    void Start();
    void Update();
    void postUpdate();
};

