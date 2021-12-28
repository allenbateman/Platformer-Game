#pragma once
#include "Module.h"
#include "p2List.h"
#include "App.h"

#define MAX_ENTITIES 100
#define SPAWN_MARGIN 20

enum EntityType {
	No_Type,
	BAT,
	MUSHER
};

struct EntitySpawnpoint
{
	EntityType type = EntityType::No_Type;
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
	bool CleanUp() override;

	// Load / Save
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

	EntitySpawnpoint spawnQueue[MAX_ENTITIES];

	// All spawned enemies in the scene
	Entity* entities[MAX_ENTITIES] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;
};

