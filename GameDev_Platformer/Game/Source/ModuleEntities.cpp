#include "ModuleEntities.h"
#include "Point.h"
#include "Entity.h"

#include "Bat.h"
#include "Musher.h"
#include "Gem.h"
#include "Key.h"
#include "HPotion.h"
#include "CheckPoint.h"
#include "Portal.h"



ModuleEntities::ModuleEntities(bool isActive) : Module(isActive)
{
    name.Create("entities");
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
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {

        if (entities[i] != nullptr)
        {
            entities[i]->Start();
        }
    }

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
            entities[i]->PostUpdate();
        
    }
    return true;
}

bool ModuleEntities::CleanUp()
{
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] != nullptr)
        {
            entities[i]->Cleanup();
            delete entities[i];
            entities[i] = nullptr;
        }
    }
    return true;
}

void ModuleEntities::AddEntity(Collider_Type type, iPoint spawnPos)
{
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] == nullptr)
        {
            switch (type)
            {
            case BAT:
                entities[i] = new Bat(type, spawnPos);
                break;
            case MUSHER:
                entities[i] = new Musher(type, spawnPos);
                break;
            case PLAYER:
                break;
            case KEY:
                entities[i] = new Key(type,spawnPos);
                break;
            case GEM:
                entities[i] = new Gem(type,spawnPos);
                break;
            case POTION:
                entities[i] = new HPotion(type, spawnPos);
                break;
            case CHECK_POINT:
                entities[i] = new CheckPoint(type, spawnPos);
                break;
            case WIN:
                entities[i] = new Portal(type, spawnPos);
            default :
                break;
            }

            break;
        }
    }
}

void ModuleEntities::RemoveEntity(PhysBody* entity)
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        if (entities[i]!= nullptr && entity == entities[i]->physBody)
        {
            entities[i]->physBody->pendingToDelete = true;
            entities[i]->Cleanup();
          
            delete entities[i];
            entities[i] = nullptr;

        }
    }
}


bool ModuleEntities::LoadState(pugi::xml_node& data)
{

    //clear all entities to load new ones
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] != nullptr)
        {
            entities[i]->Cleanup();
            delete entities[i];
            entities[i] = nullptr;
        }
    }

    pugi::xml_node currentEntitie = data.first_child();

    iPoint pos;

    while (currentEntitie != NULL )
    {
        Collider_Type type = static_cast<Collider_Type>(currentEntitie.attribute("type").as_int());
       float x = currentEntitie.attribute("x").as_int();
       float y = currentEntitie.attribute("y").as_int();


       for (uint i = 0; i < MAX_ENTITIES; ++i)
       {
           if (entities[i] == nullptr)
           {
               pos = app->map->MapToWorld(x, y);
               pos.x += 8;
               pos.y += 8;
               AddEntity(type, pos);
               break;
           }
       }
       currentEntitie = currentEntitie.next_sibling();
    }

    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] != nullptr)
        {
            entities[i]->Start();
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
