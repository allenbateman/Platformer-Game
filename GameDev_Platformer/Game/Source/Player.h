#pragma once
#include "Module.h"
#include "Globals.h"
#include "Point.h"
#include "Animation.h"
#include "Textures.h"

struct Player1 {
	PhysBody* player;
	Animation idlePlayerAnim;
	Animation jumpingPlayerAnim;
	Animation walkingPlayerAnim;
	enum State
	{
		IDLE,
		WALK,
		JUMP
	};
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
	Animation idlePlayerAnim, walkingPlayerAnim, jumpingPlayerAnim;
	enum State
	{
		IDLE,
		WALK,
		JUMP
	};
	State pState;
	bool IsDirectionRight;
	float maxSpeedX;
	float minSpeedX;
};