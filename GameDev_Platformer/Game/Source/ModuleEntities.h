#pragma once
#include "Module.h"
#include "p2List.h"
#include "App.h"

#define MAX_ENTITIES 100
#define SPAWN_MARGIN 20



enum class EntityType {
	NO_TYPE,
	MUSHER,
	BAT
};
struct EntitySpawnpoint
{
	EntityType type = EntityType::NO_TYPE;
	int x, y;
};

class Entity;
struct SDL_Texture;
struct PhysicBody;

class ModuleEntities :   public Module
{
public:
	ModuleEntities(bool isActive);
	~ModuleEntities();
	bool Awake();
	bool Start();
	bool PreUpdate() override;
	bool Update(float dt) override;
	bool PostUpdate() override;
	//bool CleanUp() override;


	// Iterates the queue and checks for camera position
	//void HandleEnemySpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleEnemyDespawn();

	bool AddEntity(EntityType type, int x, int y);


	void SpawnEntity(const EntitySpawnpoint& info);

	void RemoveEntity(Entity* entity);

	EntitySpawnpoint spawnQueue[MAX_ENTITIES];

	// All spawned enemies in the scene
	Entity* entities[MAX_ENTITIES] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;
};

