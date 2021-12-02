#include "Enemy.h"

Enemy::Enemy(bool isActive) : Module(isActive)
{
	name.Create("Musher");
}

Enemy::~Enemy()
{
}

bool Enemy::Awake()
{
	return false;
}

bool Enemy::Start()
{

	//Idle anim
	idleAnim.PushBack({ 41, 274, 14, 14 });
	idleAnim.PushBack({ 73, 276 , 14, 12 });
	idleAnim.loop = false;
	idleAnim.mustFlip = true;
	idleAnim.speed = 0.02f;
	//Walking anim
	walkingAnim.PushBack({ 9, 274, 14, 14 });
	walkingAnim.PushBack({ 41, 274, 14, 14 });
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

	return true;
}

bool Enemy::PreUpdate()
{
	return true;
}

bool Enemy::Update(float dt)
{
	return true;
}

bool Enemy::PostUpdate()
{
	return true;
}

bool Enemy::CleanUp()
{
	return true;
}

void Enemy::Spawn(fPoint pos)
{
}

void Enemy::Disable()
{
}

bool Enemy::LoadState(pugi::xml_node& data)
{
	return true;
}

bool Enemy::SaveState(pugi::xml_node& data) const
{
	return false;
}
