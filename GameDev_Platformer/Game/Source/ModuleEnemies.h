#pragma once
#include "Module.h"
#include "ModulePhysics.h"
#include "App.h"

enum EnemyType {
	MUSHER,
	BAT
};

class ModuleEnemies :   public Module
{
public:
	ModuleEnemies(bool isActive);
	~ModuleEnemies();
	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	PhysBody* AddEnemy(EnemyType type);

	p2List<PhysBody*> enemies;

	void RemoveEnemy(PhysBody* enemy);
};

