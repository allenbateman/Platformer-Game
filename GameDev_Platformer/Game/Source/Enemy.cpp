#include "Enemy.h"

Enemy::Enemy(iPoint pos) : Entity(pos)
{
	position.x = pos.x;
	position.y = pos.y;
}

void Enemy::Move(float dt)
{
}

void Enemy::UpdatePath()
{
}
