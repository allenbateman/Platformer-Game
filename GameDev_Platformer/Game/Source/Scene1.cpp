
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene1.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "LevelManagement.h"
#include "player.h"
#include "Musher.h"

#include "Defs.h"
#include "Log.h"

Scene1::Scene1(bool isActive) : Module(isActive)
{
	name.Create("level1");
}

// Destructor
Scene1::~Scene1()
{}

// Called before render is available
bool Scene1::Awake()
{
	LOG("Loading Scene 1");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene1::Start()
{
	app->physics->Start();
	app->map->Load("level1.tmx");

	KeysToTake = 2;
	app->player->Spawn({ 2, 26 });

	app->musher->Spawn({ 24, 27});
	app->musher->patrolPoint1 = { 27,27 };
	app->musher->patrolPoint2 = { 22,27 };

	return true;
}

// Called each loop iteration
bool Scene1::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene1::Update(float dt)
{
    // L02: DONE 3: Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();

	// Draw map
	app->map->Draw();


	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	//
//	app->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool Scene1::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene1::CleanUp()
{
	LOG("Disable scene 1");
	app->player->Disable();
	app->map->CleanUp();
	app->physics->Disable();
	
	return true;
}

void Scene1::Enable()
{
	LOG("Enable scene 1");
	Start();
}

void Scene1::Disable()
{
	LOG("Disable scene 1");
	app->player->Disable();
	app->map->CleanUp();
	app->physics->Disable();
}

bool Scene1::LoadState(pugi::xml_node& data)
{
	bool ret = true;
	pugi::xml_node level = data.child("level1");
	KeysToTake = level.attribute("keys_to_collect").as_int();
	return ret;
}

bool Scene1::SaveState(pugi::xml_node& data) const
{
	bool ret = true;
	pugi::xml_node level = data.append_child("level1");

	level.append_attribute("keys_to_collect") = KeysToTake;

	return ret;
}
void Scene1::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

	p2List_item<PhysBody*>* ToRemove;
	p2List_item<PhysBody*>* current = app->physics->collectables.getFirst();
	if (bodyA->type == Collider_Type::PLAYER)
	{
		//LOG("I got touched! A");
		switch (bodyB->type)
		{
		case Collider_Type::GEM:
			while (current != NULL)
			{
				bool removeItem = false;
				p2List_item<PhysBody*>* itemToRemove = current;
				if (current->data == bodyB) {
					removeItem = true;
					LOG("REMOVE GEM");
				}
				current = current->next;
				if (removeItem)
				{
					itemToRemove->data->pendingToDelete = true;

					Object* obj = app->map->GetObjectById(itemToRemove->data->id);
					if (!obj->properties.SetProperty("Draw", 0))
					{
						LOG("Could not change object property");
					}

					app->physics->collectables.del(itemToRemove);
				}
			}
			break;
		case Collider_Type::KEY:
			while (current != NULL)
			{
				bool removeItem = false;
				p2List_item<PhysBody*>* itemToRemove = current;
				if (current->data == bodyB) {
					removeItem = true;
					KeysToTake--;
					LOG("REMOVE KEY");
				}
				current = current->next;
				if (removeItem)
				{
					itemToRemove->data->pendingToDelete = true;

					Object* obj = app->map->GetObjectById(itemToRemove->data->id);
					if (!obj->properties.SetProperty("Draw", 0))
					{
						LOG("Could not change object property");
					}

					app->physics->collectables.del(itemToRemove);
				}
			}
			break;
		case Collider_Type::DEATH:
				app->player->state = PlayerState::DEAD;
				LOG("KILL ME!");
			break;
		case Collider_Type::WIN:
			if (KeysToTake == 0)
			{
				app->levelManagement->NextLevel();
				LOG("I WON, GIVE ME TREAT!");
			}
			break;
		case Collider_Type::GROUND:
			app->player->onGround = true;
			app->player->doubleJump= false;
			LOG("ON GROUND");
			break;
		default:
			break;
		}


	}
	else if (bodyB->type == Collider_Type::PLAYER)
	{
		//LOG("I got touched! B");
		switch (bodyA->type)
		{
		case Collider_Type::GEM:

			while (current != NULL)
			{
				bool removeItem = false;
				p2List_item<PhysBody*>* itemToRemove = current;
				if (current->data == bodyB) {
					removeItem = true;
					LOG("REMOVE GEM");
				}
				current = current->next;
				if (removeItem)
				{
					itemToRemove->data->pendingToDelete = true;

					Object* obj = app->map->GetObjectById(itemToRemove->data->id);
					if (!obj->properties.SetProperty("Draw", 0))
					{
						LOG("Could not change object property");
					}
					app->physics->collectables.del(itemToRemove);
				}
			}
			break;
		case Collider_Type::KEY:
			while (current != NULL)
			{
				bool removeItem = false;
				p2List_item<PhysBody*>* itemToRemove = current;
				if (current->data == bodyB) {
					removeItem = true;
					KeysToTake--;
					LOG("REMOVE KEY");
				}
				current = current->next;
				if (removeItem)
				{
					itemToRemove->data->pendingToDelete = true;

					Object* obj = app->map->GetObjectById(itemToRemove->data->id);
					if (!obj->properties.SetProperty("Draw", 0))
					{
						LOG("Could not change object property");
					}
					app->physics->collectables.del(itemToRemove);
				}
			}
			break;
		case Collider_Type::DEATH:
			app->player->state = PlayerState::DEAD;
			LOG("KILL ME!");
			break;
		case Collider_Type::WIN:
			if (KeysToTake == 0)
			{
				app->levelManagement->NextLevel();
				LOG("I WON, GIVE ME TREAT!");
			}

			break;
		case Collider_Type::GROUND:
			app->player->onGround = true;
			app->player->doubleJump = false;
			LOG("ON GROUND");
			break;
		default:
			break;
		}
	}

}