#ifndef __INTRO_H__
#define __INTRO_H__

#include "Module.h"
#include "p2List.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include "Animation.h"

struct SDL_Texture;

class Intro : public Module
{
public:

	Intro();

	// Destructor
	virtual ~Intro();

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

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

private:
	SDL_Texture* img;
	p2List_item<PhysBody*>* collider;
};

#endif // __INTRO_H__
