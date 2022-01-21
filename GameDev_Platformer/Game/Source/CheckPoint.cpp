#include "CheckPoint.h"

CheckPoint::CheckPoint(iPoint pos) : Entity(pos)
{
}

CheckPoint::CheckPoint(Collider_Type type, iPoint pos) : Entity(pos)
{
}

bool CheckPoint::LoadState(pugi::xml_node& data)
{
	return false;
}

bool CheckPoint::SaveState(pugi::xml_node& data) const
{
	return true;
}

bool CheckPoint::Start()
{
	texture =  app->tex->Load("Assets/Spritesx16/props.png"); 
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
	currentAnim = &idleShrineAnim;
	frameCounter = 0;

	physBody = app->physics->CreateRectangleSensor(position.x, position.y+32, 16, 48, b2_staticBody);
	physBody->color = { 25,150,25,255 };
	physBody->type = Collider_Type::CHECK_POINT;
	app->physics->allPhysicBodies.add(physBody);

//	position.x = physBody->body->GetPosition().x;
//	position.y = physBody->body->GetPosition().y;

	return true;
}

bool CheckPoint::PreUpdate()
{
	return true;
}

bool CheckPoint::Update()
{
	switch (shrineState)
	{
	case S_IDLE:
		idleShrineAnim.Update();
		break;
	case S_TRANSITION:
		transitionShrineAnim.Update();
		if (transitionShrineAnim.HasFinished())
		{
			shrineState = S_OPEN;
			currentAnim = &openShrineAnim;
		}
		break;
	case S_OPEN:
		openShrineAnim.Update();
		break;
	}

	return true;
}

bool CheckPoint::PostUpdate()
{
	app->render->DrawTexture(texture, position.x-16,position.y, &(currentAnim->GetCurrentFrame()));
	return true;
}

bool CheckPoint::Cleanup()
{
	texture = nullptr;
	currentAnim = nullptr;
	return true;
}
