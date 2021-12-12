
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

	KeysToTake = 2;

	app->player->Spawn({ 2, 26 });

	app->musher->Spawn({ 24, 27});
	app->musher->patrolPoint1 = { 28,27 };
	app->musher->patrolPoint2 = { 22,27 };

	app->bat->Spawn({54,22});

	props = app->tex->Load("Assets/Spritesx16/props.png");
	music = app->audio->LoadFx("Assets/audio/music/level1.wav");
	app->audio->PlayFx(music);

	//Portal animations
	//Idle anim
	idlePortalAnim.PushBack({ 32, 0, 32, 64 });
	idlePortalAnim.PushBack({ 64, 0, 32, 64 });
	idlePortalAnim.PushBack({ 96, 0, 32, 64 });
	idlePortalAnim.PushBack({ 64, 0, 32, 64 });
	idlePortalAnim.loop = true;
	idlePortalAnim.mustFlip = false;
	idlePortalAnim.speed = 0.05f;
	//Transition anim
	transitionPortalAnim.PushBack({ 128, 0, 32, 64 });
	transitionPortalAnim.PushBack({ 160, 0, 32, 64 });
	transitionPortalAnim.PushBack({ 192, 0, 32, 64 });
	transitionPortalAnim.PushBack({ 224, 0, 32, 64 });
	transitionPortalAnim.loop = false;
	transitionPortalAnim.mustFlip = false;
	transitionPortalAnim.speed = 0.05f;
	//Open anim
	openPortalAnim.PushBack({ 288, 0, 32, 64 });
	openPortalAnim.PushBack({ 320, 0, 32, 64 });
	openPortalAnim.PushBack({ 352, 0, 32, 64 });
	openPortalAnim.PushBack({ 320, 0, 32, 64 });
	openPortalAnim.loop = true;
	openPortalAnim.mustFlip = false;
	openPortalAnim.speed = 0.05f;
	portalState = P_IDLE;

	//Shrine (checkpoint) animations
	//Idle anim
	idleShrineAnim.PushBack({ 0, 84, 32, 60 });
	idleShrineAnim.loop = false;
	idleShrineAnim.mustFlip = false;
	idleShrineAnim.speed = 0.05f;
	//Transition anim
	transitionShrineAnim.PushBack({ 32, 84, 32, 60 });
	transitionShrineAnim.PushBack({ 64, 84, 32, 60 });
	transitionShrineAnim.loop = false;
	transitionShrineAnim.mustFlip = false;
	transitionShrineAnim.speed = 0.01f;
	//Open anim
	openShrineAnim.PushBack({ 96, 84, 32, 60 });
	openShrineAnim.loop = false;
	openShrineAnim.mustFlip = false;
	openShrineAnim.speed = 0.05f;
	shrineState = S_IDLE;

	//Player lives animations
	//1 Life animation
	lives1Anim.PushBack({ 145, 82, 48, 28 });
	lives1Anim.loop = false;
	lives1Anim.mustFlip = false;
	lives1Anim.speed = 0.05f;
	//2 Lives animation
	lives2Anim.PushBack({ 145, 82, 96, 28 });
	lives2Anim.loop = false;
	lives2Anim.mustFlip = false;
	lives2Anim.speed = 0.05f;
	//3 Lives animation
	lives3Anim.PushBack({ 145, 82, 128, 28 });
	lives3Anim.loop = false;
	lives3Anim.mustFlip = false;
	lives3Anim.speed = 0.05f;

	frameCounter1 = 0;
	frameCounter2 = 0;

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
	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();

	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	switch (portalState)
	{
	case P_IDLE:
		idlePortalAnim.Update();
		break;
	case P_TRANSITION:
		transitionPortalAnim.Update();
		break;
	case P_OPEN:
		openPortalAnim.Update();
		break;
	}

	if (frameCounter1 >= 4)
	{
		portalState = P_OPEN;
	}
	if (KeysToTake <= 0 && portalState != P_OPEN) 
	{ 
		portalState = P_TRANSITION;
		frameCounter1++;
	}

	switch (shrineState)
	{
	case S_IDLE:
		idleShrineAnim.Update();
		break;
	case S_TRANSITION:
		transitionShrineAnim.Update();
		break;
	case S_OPEN:
		openShrineAnim.Update();
		break;
	}

	if (frameCounter2 >= 2)
	{
		shrineState = S_OPEN;
	}
	else if (playerInCheckPoint && shrineState != S_OPEN)
	{
		shrineState = S_TRANSITION;
		frameCounter2++;
	}

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

	switch (portalState)
	{
	case P_IDLE:
		currentPortalAnim = &idlePortalAnim;
		break;
	case P_TRANSITION:
		currentPortalAnim = &transitionPortalAnim;
		break;
	case P_OPEN:
		currentPortalAnim = &openPortalAnim;
		break;
	}

	switch (shrineState)
	{
	case S_IDLE:
		currentShrineAnim = &idleShrineAnim;
		break;
	case S_TRANSITION:
		currentShrineAnim = &transitionShrineAnim;
		break;
	case S_OPEN:
		currentShrineAnim = &openShrineAnim;
		break;
	}

	switch (app->player->lives)
	{
	case 1:
		currentLivesAnim = &lives1Anim;
		break;
	case 2:
		currentLivesAnim = &lives2Anim;
		break;
	case 3:
		currentLivesAnim = &lives3Anim;
		break;
	}

	if (props != NULL)
	{
		app->render->DrawTexture(props, 1235, 162, &(currentPortalAnim->GetCurrentFrame()));
		app->render->DrawTexture(props, 852, 197, &(currentShrineAnim->GetCurrentFrame()));
		if (app->player->lives >= 1) app->render->DrawTexture(props, 20, 20, &(currentLivesAnim->GetCurrentFrame()));
	}

	return ret;
}

// Called before quitting
bool Scene1::CleanUp()
{
	LOG("Disable scene 1");
	app->player->Disable();
	app->musher->Disable();
	app->bat->Disable();
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
	playerInCheckPoint = level.attribute("player_in_check_point").as_bool();
	return ret;
}

bool Scene1::SaveState(pugi::xml_node& data) const
{
	bool ret = true;
	pugi::xml_node level = data.append_child("level1");

	level.append_attribute("keys_to_collect") = KeysToTake;
	level.append_attribute("player_in_check_point") = playerInCheckPoint;

	return ret;
}
void Scene1::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

	p2List_item<PhysBody*>* ToRemove;
	p2List_item<PhysBody*>* current = app->physics->collectables.getFirst();
	if (bodyA->type == Collider_Type::PLAYER )
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
		case Collider_Type::POTION:
			while (current != NULL)
			{
				bool removeItem = false;
				p2List_item<PhysBody*>* itemToRemove = current;
				if (current->data == bodyB) {
					removeItem = true;
					app->player->lives++;
					LOG("REMOVE POTION");
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
			
			if (!playerInCheckPoint)
			{
				app->SaveGameRequest();
				LOG("CHECKPOINT! PROGRESS SAVED!");
			}
			playerInCheckPoint = true;
		

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
	
	//Entities Collision
	current = app->physics->entities.getFirst();

	if (bodyA->type == Collider_Type::ENEMY && bodyB->type == Collider_Type::PLAYER_ATTACK)
	{
		if (bodyA == app->bat->physBody)
		{
			app->bat->state = app->bat->DEATH;
		}
		if (bodyA == app->musher->physBody)
		{
			app->musher->state = app->musher->DEATH;
		}
		/*while (current != NULL)
		{
			bool removeEntity = false;
			p2List_item<PhysBody*>* entityToRemove = current;
			if (current->data == bodyA) {
				if (bodyA == app->bat->physBody)
				{
					app->bat->state = app->bat->DEATH;
					if (app->bat->currentAnim == &app->bat->deathAnim && app->bat->currentAnim->HasFinished())
					{
						removeEntity = true;
						LOG("REMOVE ENEMY BAT");
					}
				}
				else if (bodyA == app->musher->physBody)
				{
					app->musher->state = app->musher->DEATH;
					removeEntity = true;
					LOG("REMOVE ENEMY MUSHER");
				}
			}
			current = current->next;
			if (removeEntity)
			{
				entityToRemove->data->pendingToDelete = true;
				app->physics->entities.del(entityToRemove);
			}
		}*/
	}
}