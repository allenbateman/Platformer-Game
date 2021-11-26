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
	ModulePlayer(bool isActive);
	virtual ~ModulePlayer();

	bool Awake();
	bool Start();
	bool Update(float dt);
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
	fPoint position;
	fPoint speed = {1,1};
	fPoint jumpForce = { 0,2 };

};