#include "ModuleEntities.h"
#include "Bat.h"
#include "Musher.h"
#include "Point.h"
#include "Entity.h"

ModuleEntities::ModuleEntities(bool isActive) : Module(isActive)
{
}

ModuleEntities::~ModuleEntities()
{
}

bool ModuleEntities::Awake()
{
    //test
    return true;
}

bool ModuleEntities::Start()
{
    return true;
}

bool ModuleEntities::PreUpdate()
{
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] != nullptr)
        {
            entities[i]->DEBUG = DEBUG;
            entities[i]->PreUpdate();
        }
    }

    return true;
}

bool ModuleEntities::Update(float dt)
{

    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] != nullptr)
            entities[i]->Update(dt);
    }

    return true;
}

bool ModuleEntities::PostUpdate()
{
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] != nullptr)
        {

            entities[i]->PostUpdate();

        }
    }
    return true;
}

bool ModuleEntities::CleanUp()
{
    return true;
}

bool ModuleEntities::LoadState(pugi::xml_node& data)
{
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] != nullptr)
        {
            entities[i]->LoadState(data);
        }
    }
    return true;
}

bool ModuleEntities::SaveState(pugi::xml_node& data) const
{
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] != nullptr)
        {
            entities[i]->SaveState(data);
        }
    }
    return true;
}
