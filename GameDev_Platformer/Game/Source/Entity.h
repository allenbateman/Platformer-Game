#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "App.h"
#include "ModulePhysics.h"
#include "Point.h"
#include "Animation.h"

struct SDL_Texture;
struct PhysicBody;

class Entity
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Entity(int x, int y);

	// Destructor
	virtual ~Entity();

	// Returns the Entity's collider
	const PhysBody* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEntitys' Update
	virtual void Draw();

	// Collision response
	virtual void OnCollision(PhysBody* collider);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

	//virtual void ChangeDirection();
	//virtual void CheckDirection();

public:
	// The current position in the world
	iPoint position;
	b2Vec2 bodyPosition;
	iPoint drawOffset = { 0, 0 };

	//EntityType type;

	// The Entity's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the Entity removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	int scorePoints = 0;

	enum Direction
	{
		UP,
		DOWN,
		RIGHT,
		LEFT,
		NONE
	};
	enum State
	{
		IDLE,
		MOVE,
		ATACK,
		DEATH,
		SCORE
	};

	State state;
	Direction direction;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;
	Animation score;

	// The Entity's collider
	PhysBody* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __ENTITY_H__