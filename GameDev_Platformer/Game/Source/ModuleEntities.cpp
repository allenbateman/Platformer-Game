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

//bool ModuleEntities::CleanUp()
//{
//    LOG("Freeing all entities");
//
//    for (uint i = 0; i < MAX_ENTITIES; ++i)
//    {
//        if (entities[i] != nullptr)
//        {
//            delete entities[i];
//            entities[i] = nullptr;
//        }
//    }
//
//    return true;
//}



bool ModuleEntities::AddEntity(EntityType type, int x, int y)
{
    bool ret = true;
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (spawnQueue[i].type == EntityType::NO_TYPE)
        {
            spawnQueue[i].type = type;
            spawnQueue[i].x = x;
            spawnQueue[i].y = y;
            ret = true;
            break;
        }
    }

    return ret;
}

//void ModuleEntities::SpawnEntity(const EntitySpawnpoint& info)
//{
//    // Iterate all the entities queue
//    for (uint i = 0; i < MAX_ENTITIES; ++i)
//    {
//        if (spawnQueue[i].type != EntityType::NO_TYPE)
//        {
//            // Spawn a new Entitie if the screen has reached a spawn position
//            if (spawnQueue[i].x * SCREEN_SIZE < app->render->camera.x + (app->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
//            {
//                LOG("Spawning Entity at %d", spawnQueue[i].x * SCREEN_SIZE);
//
//                SpawnEntity(spawnQueue[i]);
//                spawnQueue[i].type = EntityType::NO_TYPE; // Removing the newly spawned Entitie from the queue
//            }
//        }
//    }
//}

void ModuleEntities::RemoveEntity(Entity* entity)
{
    // Iterate existing entities
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] != nullptr)
        {

        }
    }
}
