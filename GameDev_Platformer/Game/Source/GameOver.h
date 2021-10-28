#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "Module.h"
#include "p2List.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include "Animation.h"

struct SDL_Texture;

class GameOver : public Module
{
public:

	GameOver();

	// Destructor
	virtual ~GameOver();

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
};

#endif // __GAMEOVER_H__
