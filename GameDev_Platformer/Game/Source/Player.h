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

	void Movement();
	void GodMovement();
	void UpdateSensorsPosition();

	//attacks
	void MeleeAttack();
	void RangedAttack();
	//skills?

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	// Load / Save
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

	SDL_Texture* playerTexture;

public:
	Animation* currentAnim = nullptr;
	Animation idlePlayerAnim, walkingPlayerAnim, jumpingPlayerAnim, deathPlayerAnim, meleePlayerAnim;
	
	float jumpForce = 8;
	float onAirXSpeed = 5;
	bool doubleJump = false;
	bool onGround = false;
	bool onAir = false;
	PlayerState state;
	SDL_RendererFlip direction;
	fPoint lastPosition;
	fPoint position;
	fPoint speed = {10,10};
	PhysBody* physBody;
	PhysBody* leftSensor;
	PhysBody* rightSensor;
	PhysBody* botSensor;
	PhysBody* topSensor;
	
	int colliderRadius = 8;

	int score = 0;

	int lives;
	bool isGodmodeOn = false;
	bool LoadRequest = false;

	int frameCounter;
};