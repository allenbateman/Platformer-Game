#pragma once
#include "Module.h"
#include "p2List.h"
#include "App.h"
#include "ModulePhysics.h"
#include "Point.h"

#define MAX_ENTITIES 100
#define SPAWN_MARGIN 20

enum EntityType {
	No_Type,
	BAT,
	MUSHER,
	GEM,
	KEY,
	PLAYER,
	CHECK_POINT
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
	void AddEntity(EntityType type ,iPoint spawnPos);

	// Load / Save
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

	// All spawned enemies in the scene
	Entity* entities[MAX_ENTITIES] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;
};

