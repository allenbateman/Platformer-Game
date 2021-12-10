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
	void SetPosition(iPoint pos);
	fPoint GetPosition() { return position; };
	void Spawn(iPoint pos);
	void Disable();

	// Load / Save
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

	SDL_Texture* playerTexture;

public:
	Animation* currentAnim = nullptr;
	Animation idlePlayerAnim, walkingPlayerAnim, jumpingPlayerAnim, deathPlayerAnim, meleePlayerAnim;
	
	float jumpForce = 5;
	bool doubleJump = false;
	bool onGround = false;
	bool onAir = false;
	PlayerState state;
	SDL_RendererFlip direction;
	fPoint position;
	fPoint speed = {5,5};
	PhysBody* physBody;
	PhysBody* leftSensor;
	PhysBody* rightSensor;
	PhysBody* botSensor;
	PhysBody* topSensor;
<<<<<<< Updated upstream
	
	int score = 0;
=======

	int lives;
	bool isGodmodeOn;

>>>>>>> Stashed changes
	int frameCounter;
};