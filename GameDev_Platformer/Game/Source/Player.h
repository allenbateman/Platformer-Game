#pragma once
#include "Module.h"
#include "Globals.h"
#include "Point.h"
#include "Animation.h"

struct Player1 {
	PhysBody* player;
	Animation idlePlayerAnim;
	Animation deathPlayerAnim;
	Animation walkingPlayerAnim;
	enum State
	{
		IDLE,
		DEAD,
		SPAWN
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

public:
	Player1* p;
	float maxSpeedX;
	float minSpeedX;
};