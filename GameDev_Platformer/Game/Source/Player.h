#pragma once
#include "Module.h"
#include "Globals.h"
#include "Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Render.h"

struct Player1 {
	PhysBody* player;
	Animation idlePlayerAnim;
	Animation jumpingPlayerAnim;
	Animation walkingPlayerAnim;
	Animation deathPlayerAnim;
	bool IsDirectionRight;
};

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	virtual ~ModulePlayer();


	bool Start();
	bool Update(float dt);
	bool CleanUp();

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	SDL_Texture* playerTexture;

public:
	Player1* p;
	Animation* currentAnim = nullptr;
	Animation idlePlayerAnim, walkingPlayerAnim, jumpingPlayerAnim, deathPlayerAnim;
	enum State
	{
		IDLE,
		WALK,
		JUMP,
		DEATH
	};
	State pState;
	bool IsDirectionRight;
	float maxSpeedX;
	float minSpeedX;
	SDL_RendererFlip direction;
};