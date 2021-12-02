#include "Musher.h"
#include "Globals.h"
#include "App.h"
#include "Input.h"
#include "ModulePhysics.h"
#include "LevelManagement.h"
#include "Render.h"
#include "Log.h"

Musher::Musher(bool isActive) : Module(isActive)
{
	name.Create("Musher");
}

Musher::~Musher()
{
}

bool Musher::Awake()
{
	return true;
}

bool Musher::Start()
{
	texture = app->tex->Load("Assets/Spritesx16/characters.png");
	//Idle anim
	idleAnim.PushBack({ 41, 274, 14, 14 });
	idleAnim.PushBack({ 73, 276 , 14, 12 });
	idleAnim.loop = true;
	idleAnim.mustFlip = true;
	idleAnim.speed = 0.01f;
	//Walking anim
	walkingAnim.PushBack({ 9, 274, 14, 14 });
	walkingAnim.PushBack({ 41, 274, 14, 14});
	walkingAnim.PushBack({ 73, 276 , 14, 12 });
	walkingAnim.loop = true;
	walkingAnim.mustFlip = true;
	walkingAnim.speed = 0.1f;
	//Jump anim
	jumpingAnim.PushBack({ 137, 274, 14, 14 });
	jumpingAnim.PushBack({ 168, 272, 14, 14 });
	jumpingAnim.PushBack({ 201, 272, 14, 15 });
	jumpingAnim.PushBack({ 233, 275, 14, 13 });
	jumpingAnim.loop = true;
	jumpingAnim.mustFlip = true;
	jumpingAnim.speed = 0.1f;

	currentAnim = &idleAnim;

	position = { 20, 300 };
	physBody = app->physics->CreateCircle(position.x, position.y, 7, b2_dynamicBody, { 0,250,125,255 });
	physBody->listener = app->levelManagement->currentScene;
	physBody->color = {255,125,0,255};

	physBody->body->SetFixedRotation(true);
	app->physics->entities.add(physBody);

	pathfinding = new PathFinding(true);
	pathfinding->CreatePath({(int) position.x,(int)position.y }, { 400,301 });

	LOG("MUSER START");
	return true;
}

bool Musher::PreUpdate()
{
	return true;
}

bool Musher::Update(float dt)
{

	return true;
}

bool Musher::PostUpdate()
{
	currentAnim->Update();
	if(texture!=nullptr)
	app->render->DrawTexture(texture, METERS_TO_PIXELS(physBody->body->GetPosition().x-14), METERS_TO_PIXELS(physBody->body->GetPosition().y-14),
		&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
	return true;
}

bool Musher::CleanUp()
{
	return true;
}

void Musher::Spawn(fPoint pos)
{
	Enable();
	SetPosition(pos);
}

bool Musher::LoadState(pugi::xml_node& data)
{
	return true;
}

bool Musher::SaveState(pugi::xml_node& data) const
{
	return true;
}
