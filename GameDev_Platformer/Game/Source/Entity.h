#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "App.h"
#include "ModulePhysics.h"
#include "Globals.h"
#include "Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Render.h"

struct SDL_Texture;
struct PhysicBody;

class Entity abstract
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Entity(iPoint position);

	// Destructor
	virtual ~Entity();

	// Returns the Entity's collider
	const PhysBody* GetCollider() const;

	virtual bool PreUpdate();
	// Updates animation and collider position
	virtual bool Update(float dt);

	// Called from ModuleEntitys' Update
	virtual bool PostUpdate();

	// Collision response
	virtual void OnCollision(PhysBody* other);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

	// Load / Save
	virtual bool LoadState(pugi::xml_node& data);
	virtual bool SaveState(pugi::xml_node& data) const;

public:
	// The current position in the world
	fPoint position;
	b2Vec2 bodyPosition;
	iPoint drawOffset = { 0, 0 };

	//type of collider
	Collider_Type type;

	// The Entity's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the Entity removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	//if debug mode
	bool DEBUG;

	//If Enemy
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
	PhysBody* physBody = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;

};

#endif // __ENTITY_H__