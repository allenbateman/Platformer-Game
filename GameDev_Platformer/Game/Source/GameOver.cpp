#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "GameOver.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "player.h"

#include "Defs.h"
#include "Log.h"

GameOver::GameOver() : Module()
{
	name.Create("scene");
}

// Destructor
GameOver::~GameOver()
{}

// Called before render is available
bool GameOver::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool GameOver::Start()
{
	// L03: DONE: Load map
	//app->map->Load("iso_walk.tmx");
	app->map->Load("level1.tmx");

	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

	return true;
}

// Called each loop iteration
bool GameOver::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool GameOver::Update(float dt)
{
	// L02: DONE 3: Request Load / Save when pressing L/S
	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();

	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

	// Draw map
	app->map->Draw();

	// L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width, app->map->mapData.height,
		app->map->mapData.tileWidth, app->map->mapData.tileHeight,
		app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool GameOver::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool GameOver::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool GameOver::LoadState(pugi::xml_node&)
{
	bool ret = true;
	return ret;
}

bool GameOver::SaveState(pugi::xml_node&) const
{
	bool ret = true;
	return ret;
}