#include "Gem.h"

void Gem::Start()
{

	texture = app->tex->Load("../Output/Assets/Spritesx16/gems.png");
	r.x = position.x;
	r.y = position.y;
	r.w = 16;
	r.h = 16;
	physBody = app->physics->CreateRectangleSensor(r.x + (r.w * 0.5f), r.y - (r.h * 0.5f), r.w, r.h, b2_staticBody);
	physBody->color = { 100,50,255,255 };
	physBody->type = Collider_Type::GEM;
	app->physics->collectables.add(physBody);
}

void Gem::Update()
{
}

void Gem::postUpdate()
{
	r.x = 0;//position in the texture
	if (texture != NULL)
		app->render->DrawTexture(texture, r.x, r.y - r.h, &r);
}
