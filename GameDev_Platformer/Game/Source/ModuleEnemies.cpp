#include "ModuleEnemies.h"
#include "Bat.h"
#include "Musher.h"


ModuleEnemies::ModuleEnemies(bool isActive) : Module(isActive)
{
}

ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Awake()
{
    return true;
}

bool ModuleEnemies::Start()
{
    return true;
}

bool ModuleEnemies::PreUpdate()
{
    //p2List_item<PhysBody*>* current = enemies.getFirst();
    //while (current != NULL)
    //{
    //    bool removeItem = false;
    //    p2List_item<PhysBody*>* itemToRemove = current;
    //    if (itemToRemove->data->pendingToDelete) {
    //        removeItem = true;
    //    }
    //    current = current->next;
    //    if (removeItem && itemToRemove->data->body != NULL)
    //    {
    //        LOG("Removing item ");
    //        app->physics->RemoveBodyFromWorld(itemToRemove->data->body);
    //        enemies.del(itemToRemove);
    //    }
    //}
    return true;
}

bool ModuleEnemies::Update(float dt)
{
    //p2List_item<PhysBody*>* current = enemies.getFirst();
    //while (current != NULL)
    //{
    //}
    return true;
}

bool ModuleEnemies::PostUpdate()
{
    return true;
}

bool ModuleEnemies::CleanUp()
{
    return true;
}

PhysBody* ModuleEnemies::AddEnemy(EnemyType type)
{
    //switch (type)
    //{
    //case MUSHER:
    //    //Musher* musher = new Musher(true);
    //    //enemies.add(musher->physBody);
    //    //return  musher->physBody;
    //    return nullptr;
    //    break;
    //case BAT:
    //    //Bat* bat = new Bat(true);
    //    //enemies.add(bat->physBody);
    //    //return  bat->physBody;
    //    return nullptr;
    //    break;
    //default:
    //    return nullptr;
    //    break;
    //}
    return nullptr;
}

void ModuleEnemies::RemoveEnemy(PhysBody* enemy)
{
    //p2List_item<PhysBody*>* current = enemies.getFirst();
    //while (current != NULL)
    //{
    //    bool removeItem = false;
    //    p2List_item<PhysBody*>* itemToRemove = current;
    //    if (itemToRemove->data->pendingToDelete) {
    //        removeItem = true;
    //    }
    //    current = current->next;
    //    if (removeItem && itemToRemove->data->body != NULL)
    //    {
    //        LOG("Removing item ");
    //        app->physics->RemoveBodyFromWorld(itemToRemove->data->body);
    //        enemies.del(itemToRemove);
    //    }
    //}
}
