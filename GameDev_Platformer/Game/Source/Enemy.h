#pragma once
#include "Module.h"
#include "Globals.h"
#include "Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Render.h"
#include "Pathfinding.h"
class Enemy :
    public Module
{

public:
	Enemy(bool isActive);
	virtual ~Enemy();

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void SetPosition(fPoint pos) { position = pos; };
	fPoint GetPosition() { return position; };
	void Spawn(fPoint pos);
	void Disable();

	// Load / Save
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

	SDL_Texture* playerTexture;

public:
	Animation* currentAnim = nullptr;
	Animation idleAnim, walkingAnim, jumpingAnim, deathAnim;

	float jumpForce = 0.2f;
	bool doubleJump = false;
	bool onGround = false;
	SDL_RendererFlip direction;
	fPoint position;
	fPoint speed = { 2,2 };
	PhysBody* physBody;

	PathFinding* pathfinding;
};

