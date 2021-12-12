#pragma once
#include "Module.h"
#include "Globals.h"
#include "Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Render.h"
#include "Pathfinding.h"




class Bat : public Module
{
public:
	Bat(bool isActive);
	virtual ~Bat();

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void SetPosition(iPoint pos);
	fPoint GetPosition() { return position; };
	void Spawn(iPoint pos);
	// Load / Save
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;
	bool CalculateNextPatrolPoint();
	void UpdatePath();
	void Move(float dt);

	SDL_Texture* texture;

public:
	Animation* currentAnim = nullptr;
	Animation idleAnim, deathAnim;

	float jumpForce = 0.2f;
	bool onGround = false;

	float detectionDistance = 10; // in pixels
	int counter = 0;

	SDL_RendererFlip spriteDir;
	int spriteRotation = 0;
	fPoint position;
	fPoint lastPosition;
	fPoint playerPos;
	PhysBody* physBody;

	PathFinding* pathfinding;

	//in Tiles
	iPoint patrolPoint1;
	iPoint patrolPoint2;
	bool OnPatrolPoint = false;
	bool LoadRequest = false;

	float speedMultiplier = 0.2f;// 1-0   1->slowest-> 0.1 fastest;

	enum BatState {
		PATROL = 0,
		MOVE_TOWARDS = 1,
		JUMP = 2,
		DEATH = 3
	};
	BatState state;


	int curretnTileIndex = 0;

};
