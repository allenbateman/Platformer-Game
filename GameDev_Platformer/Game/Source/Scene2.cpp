#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene2.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "player.h"

#include "Defs.h"
#include "Log.h"

Scene2::Scene2(bool isActive) : Module(isActive)
{
	name.Create("level2");
}

// Destructor
Scene2::~Scene2()
{}

// Called before render is available
bool Scene2::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene2::Start()
{

	img = app->tex->Load("Assets/Spritesx16/ToBeContinued.png");
	//loadMap
	return true;
}

// Called each loop iteration
bool Scene2::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene2::Update(float dt)
{
	rect.x = 0;
	rect.y = 0;
	rect.w = 1280;
	rect.h = 480;
	if (img != nullptr && active)
		app->render->DrawTexture(img, 0, 0, &rect, 1.0f, 0.0f, 1, 1, 1, SDL_FLIP_NONE);
	return true;
}

// Called each loop iteration
bool Scene2::PostUpdate()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool Scene2::CleanUp()
{
	LOG("Freeing scene 2");

	return true;
}

bool Scene2::LoadState(pugi::xml_node&)
{
	bool ret = true;
	return ret;
}

bool Scene2::SaveState(pugi::xml_node&) const
{
	bool ret = true;
	return ret;
}
void Scene2::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	b2Vec2 position;

	LOG("I got touched!");


	if (bodyA->type == Collider_Type::GEM || bodyB->type == Collider_Type::GEM)
	{
		LOG("GOT A GEM!");
	}

	if (bodyA->type == Collider_Type::DEATH || bodyB->type == Collider_Type::DEATH)
	{
		LOG("I DIED!");
	}
}