#include "Portal.h"
#include "ModuleEntities.h"

Portal::Portal(iPoint pos) : Entity(pos)
{
}

Portal::Portal(Collider_Type type, iPoint pos) : Entity(pos)
{
}

bool Portal::LoadState(pugi::xml_node& data)
{
	return false;
}

bool Portal::SaveState(pugi::xml_node& data) const
{
	return false;
}

bool Portal::Start()
{
	texture = app->tex->Load("Assets/Spritesx16/props.png");
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
	currentAnim = &idlePortalAnim;

	physBody = app->physics->CreateRectangleSensor(position.x, position.y+48, 32, 64, b2_staticBody);
	physBody->listener = app->entities;
	physBody->color = { 25,150,25,255 };
	physBody->type = Collider_Type::WIN;
	app->physics->allPhysicBodies.add(physBody);


	return true;
}

bool Portal::PreUpdate()
{
	return true;
}

bool Portal::Update()
{

	switch (portalState)
	{
	case P_IDLE:
		idlePortalAnim.Update();
		break;
	case P_TRANSITION:
		transitionPortalAnim.Update();
		if (transitionPortalAnim.HasFinished())
		{
			portalState = P_OPEN;
			currentAnim = &openPortalAnim;
		}
		break;
	case P_OPEN:
		openPortalAnim.Update();
		break;
	}

	return true;
}

bool Portal::PostUpdate()
{
	app->render->DrawTexture(texture, position.x-16, position.y+16, &(currentAnim->GetCurrentFrame()));
	return true;
}

bool Portal::Cleanup()
{
	texture = nullptr;
	currentAnim = nullptr;
	return true;
}
