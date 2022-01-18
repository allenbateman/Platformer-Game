#include "Gem.h"


Gem::Gem(iPoint pos) : Collectable(pos)
{
	spawnPos = pos;
}

Gem::Gem(Collider_Type type, iPoint pos) : Collectable(pos)
{
}

bool Gem::Start()
{

	texture = app->tex->Load("../Output/Assets/Spritesx16/gems.png");

	r.x = position.x;
	r.y = position.x;
	r.w = 16;
	r.h = 16;
	//physBody = app->physics->CreateRectangleSensor(tp.x + r.w * 0.5, tp.y - r.w * 0.5, r.w, r.h, b2_staticBody);
	physBody = app->physics->CreateRectangleSensor(position.x, position.y, r.w, r.h, b2_staticBody);
	physBody->color = { 100,50,255,255 };
	physBody->type = Collider_Type::GEM;
	app->physics->allPhysicBodies.add(physBody);

	position.x = physBody->body->GetPosition().x;
	position.y = physBody->body->GetPosition().y;

	return true;
}

bool Gem::Update()
{
	return true;
}

bool Gem::PostUpdate()
{
	bool ret = true;
	r.x = 0;//position in the texture
	r.y = 0;
	r.w = 16;
	r.h = 16;
	if (texture != NULL)
		app->render->DrawTexture(texture, METERS_TO_PIXELS(physBody->body->GetPosition().x) - r.w * 0.5, METERS_TO_PIXELS(physBody->body->GetPosition().y) - r.h * 0.5, &r);

	return ret;
}

bool Gem::Cleanup()
{
	return true;
}

bool Gem::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	//position.x = data.child("Gem").attribute("x").as_int();
	//position.y = data.child("Gem").attribute("y").as_int();

	return ret;
}

bool Gem::SaveState(pugi::xml_node& data) const
{
	bool ret = true;
	pugi::xml_node entity = data.append_child("Gem");
	entity.append_attribute("type") = type;
	entity.append_attribute("x") = position.x;
	entity.append_attribute("y") = position.y;

	return ret;
}

