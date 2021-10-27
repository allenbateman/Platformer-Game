#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "p2List.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include "Animation.h"

struct SDL_Texture;

struct PlayerInScene
{
	PhysBody* player;
	Animation idlePlayerAnim;
	Animation walkingPlayerAnim;
	enum State
	{
		IDLE,
		DEAD,
		WALKING
	};
	int speed;
};

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();


	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

private:
	SDL_Texture* img;
	p2List_item<PhysBody*>* collider;
};

#endif // __SCENE_H__