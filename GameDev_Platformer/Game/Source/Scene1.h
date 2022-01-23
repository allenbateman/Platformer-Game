#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "Module.h"
#include "p2List.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include "Animation.h"

struct SDL_Texture;

class Scene1 : public Module
{
public:

	Scene1(bool isActive);

	// Destructor
	virtual ~Scene1();

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

	void Enable();
	void Disable();

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	int KeysToTake = 2;
private:
	SDL_Texture* img;
	p2List_item<PhysBody*>* collider;


	Animation* currentLivesAnim = nullptr;
	Animation*	lives2Anim, lives3Anim;
	uint music;
};

#endif // __SCENE1_H__