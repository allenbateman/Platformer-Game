#pragma once
#include "Module.h"

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

	void AddEnemy();
	void RemoveEnemy();
};

