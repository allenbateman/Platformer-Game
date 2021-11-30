#pragma once
#include "Module.h"
#include "Globals.h"
#include "Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Render.h"



enum PlayerState
{
	IDLE,
	MOVE_LEFT,
	MOVE_RIGHT,
	JUMP,
	DOUBLE_JUMP,
	ATTACK,
	DEAD
};
class ModulePlayer : public Module
{
public:
	ModulePlayer(bool isActive);
	virtual ~ModulePlayer();

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
	Animation idlePlayerAnim, walkingPlayerAnim, jumpingPlayerAnim, deathPlayerAnim;
	
	float jumpForce = 0.2f;
	bool doubleJump = false;
	bool onGround = false;
	PlayerState state;
	SDL_RendererFlip direction;
	fPoint position;
	fPoint speed = {2,2};
	PhysBody* physBody;

};