
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Animation.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene1.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "LevelManagement.h"
#include "ModuleEntities.h"
#include "player.h"
#include "Musher.h"
#include "Bat.h"

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
//	app->audio->PlayMusic("Assets/audio/music/level1.wav");

	KeysToTake = 2;

	//Spawn all entities
	app->player->Spawn({ 2, 26 });
	app->entities->Start();

	////Player lives animations
	////1 Life animation
	//lives1Anim.PushBack({ 145, 82, 48, 28 });
	//lives1Anim.loop = false;
	//lives1Anim.mustFlip = false;
	//lives1Anim.speed = 0.05f;
	////2 Lives animation
	//lives2Anim.PushBack({ 145, 82, 96, 28 });
	//lives2Anim.loop = false;
	//lives2Anim.mustFlip = false;
	//lives2Anim.speed = 0.05f;
	////3 Lives animation
	//lives3Anim.PushBack({ 145, 82, 128, 28 });
	//lives3Anim.loop = false;
	//lives3Anim.mustFlip = false;
	//lives3Anim.speed = 0.05f;

	return true;
}

// Called each loop iteration
bool Scene1::PreUpdate()
{
	if (app->player->isGodmodeOn) app->player->lives = 3;

	return true;
}

// Called each loop iteration
bool Scene1::Update(float dt)
{
    // L02: DONE 3: Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_F5))
		app->SaveGameRequest();

	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());



	return true;
}

// Called each loop iteration
bool Scene1::PostUpdate()
{
	bool ret = true;

	// Draw functions
	app->map->Draw();
	app->physics->DrawColliders();

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;
	//switch (app->player->lives)
	//{
	//case 1:
	//	currentLivesAnim = &lives1Anim;
	//	break;
	//case 2:
	//	currentLivesAnim = &lives2Anim;
	//	break;
	//case 3:
	//	currentLivesAnim = &lives3Anim;
	//	break;
	//}

	//	if (app->player->lives >= 1) app->render->DrawTexture(props, 20, 20, &(currentLivesAnim->GetCurrentFrame()));
	

	return ret;
}

// Called before quitting
bool Scene1::CleanUp()
{
	LOG("Disable scene 1");
	app->player->Disable();
	app->map->CleanUp();
	app->entities->CleanUp();
	app->physics->CleanUp();
	app->audio->PlayMusic("");
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
	app->entities->Disable();
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
	p2List_item<PhysBody*>* current = app->physics->allPhysicBodies.getFirst();
	if (bodyA->type == Collider_Type::PLAYER )
	{

		switch (bodyB->type)
		{
		case Collider_Type::GEM:
			app->entities->RemoveEntity(bodyB);
			break;
		case Collider_Type::KEY:
			app->entities->RemoveEntity(bodyB);
			break;		
		case Collider_Type::POTION:
			app->entities->RemoveEntity(bodyB);			
			break;
		case Collider_Type::DEATH:

			if(!app->player->isGodmodeOn)
				app->player->state = PlayerState::DEAD;

			LOG("KILL ME!");

			break;
		case Collider_Type::ENEMY:
			if (!app->player->isGodmodeOn)
			{
				app->player->lives--;
				LOG("OUCH GOT HIT!");
				if (app->player->lives <= 0)
				{
					app->player->state = PlayerState::DEAD;
					LOG("KILL ME!");
				}
			}
			break;
		case Collider_Type::WIN:
			if (KeysToTake == 0)
			{
				app->levelManagement->NextLevel();
				LOG("I WON, GIVE ME TREAT!");
			}
		case Collider_Type::CHECK_POINT:
			
			//if (!playerInCheckPoint)
			//{
			//	app->SaveGameRequest();
			//	LOG("CHECKPOINT! PROGRESS SAVED!");
			//}
			break;
		default:
			break;
		}

	}
	
	//Entities Collision
	current = app->physics->allPhysicBodies.getFirst();

	if (bodyA->type == Collider_Type::ENEMY && bodyB->type == Collider_Type::PLAYER_ATTACK)
	{
		app->entities->RemoveEntity(bodyA);
		bodyA->pendingToDelete = true;
	}
}