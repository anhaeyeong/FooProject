#include "Collider.h"
#include "Rocket.h"
#include "Missile.h"
#include "CommonFunction.h"

bool Collider::CollisionCheck()
{
	isCollision = RectInRect(colliderRect, obstacleRect);

	return isCollision;
}

void Collider::Init()
{
}

void Collider::Release()
{
}

void Collider::Update()
{
}

void Collider::Render(HDC hdc)
{
}

void Collider::setObstaclePos()
{
	obstaclePos = obstacle->GetPos();
}

void Collider::setColliderPos()
{
	colliderPos = collider->GetPos();
}

void Collider::setObstacleRect()
{
	obstacleRect = obstacle->GetRect();
}

void Collider::setColliderRect()
{
	colliderRect = collider->GetRect();
}
