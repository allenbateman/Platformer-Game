#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "Module.h"
#include "p2List.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include "Animation.h"

struct SDL_Texture;

enum PortalState
{
	P_IDLE,
	P_TRANSITION,
	P_OPEN
};

enum ShrineState
{
	S_IDLE,
	S_TRANSITION,
	S_OPEN
};

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

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	int KeysToTake = 2;
	bool playerInCheckPoint = false;
private:
	SDL_Texture* img;
	SDL_Texture* props;
	p2List_item<PhysBody*>* collider;

	Animation* currentPortalAnim = nullptr;
	Animation* currentShrineAnim = nullptr;
	Animation* currentLivesAnim = nullptr;
	Animation idlePortalAnim, transitionPortalAnim, openPortalAnim, idleShrineAnim, transitionShrineAnim, openShrineAnim, lives1Anim,
		lives2Anim, lives3Anim;
	uint music;

	PortalState portalState;
	ShrineState shrineState;

	int frameCounter1;
	int frameCounter2;
};

#endif // __SCENE1_H__