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
	name.Create("scene");
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
	app->physics->Start();
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
	app->map->CleanUp();
	app->physics->CleanUp();
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