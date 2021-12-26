#include "Entity.h"

#include "App.h"
#include "ModulePhysics.h"
#include "Audio.h"
#include "Render.h"
#include "Player.h"

Entity::Entity(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Entity::~Entity()
{
	if (physBody != nullptr)
		physBody->pendingToDelete = true;
}

const PhysBody* Entity::GetCollider() const
{
	return physBody;
}

bool Entity::PreUpdate()
{
	
	return true;
}

bool Entity::Update(float dt)
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (physBody != nullptr)
		physBody->body->SetTransform(bodyPosition, physBody->body->GetAngle());
	return true;
}

bool Entity::PostUpdate()
{
	if (currentAnim != nullptr) {
		if (currentAnim->mustFlip == false) app->render->DrawTexture(texture, position.x + drawOffset.x, position.y + drawOffset.y, &(currentAnim->GetCurrentFrame()));
		else app->render->DrawTexture(texture, position.x + drawOffset.x, position.y + drawOffset.y, &(currentAnim->GetCurrentFrame()), 1.0f, true, SDL_FLIP_NONE);
	}
	return true;
}

void Entity::OnCollision(PhysBody* other)
{

}

void Entity::SetToDelete()
{
	pendingToDelete = true;
	if (physBody != nullptr)
		physBody->pendingToDelete = true;
}

bool Entity::LoadState(pugi::xml_node& data)
{
	return true;
}

bool Entity::SaveState(pugi::xml_node& data) const
{
	return true;
}
