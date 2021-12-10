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
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const PhysBody* Entity::GetCollider() const
{
	return collider;
}

void Entity::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->body->SetTransform(bodyPosition,collider->body->GetAngle());
}

void Entity::Draw()
{
	if (currentAnim != nullptr) {
		if (currentAnim->mustFlip == false) app->render->DrawTexture(texture, position.x + drawOffset.x, position.y + drawOffset.y, &(currentAnim->GetCurrentFrame()));
		else app->render->DrawTexture(texture, position.x + drawOffset.x, position.y + drawOffset.y, &(currentAnim->GetCurrentFrame()), 1.0f, true, SDL_FLIP_NONE);
	}
}

void Entity::OnCollision(PhysBody* collider)
{
	SetToDelete();
}

void Entity::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
	app->player->score += scorePoints;
}
