#include "ModuleEnemies.h"

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
    return true;
}

bool ModuleEnemies::Update(float dt)
{
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

void ModuleEnemies::AddEnemy()
{
}

void ModuleEnemies::RemoveEnemy()
{
}
