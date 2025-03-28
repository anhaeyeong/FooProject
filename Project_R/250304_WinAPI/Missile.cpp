#include "Missile.h"
#include "CommonFunction.h"
#include "Rocket.h"

void Missile::Init()
{
	pos = { 0, 0 };
	isActived = false;
	moveSpeed = 3.0f;
	size = 10;

	image = ImageManager::GetInstance()->AddImage(
		"bullet", TEXT("Image/bullet.bmp"), 21, 21,
		true, RGB(255, 0, 255));
}

void Missile::Release()
{

}

void Missile::Update()
{
	Move();
	if (isActived && IsOutofScreen())
	{
		isActived = false;
	}
}

void Missile::Render(HDC hdc)
{
	if (isActived)
	{
		image->Render(hdc, pos.x, pos.y);
	}
}


void Missile::Move()
{
	if (isActived)
	{
		pos.x += moveSpeed * TimerManager::GetInstance()->GetDeltaTime() * 100
			* cosf(DEG_TO_RAD(angle));
		pos.y -= moveSpeed * TimerManager::GetInstance()->GetDeltaTime() * 100
			* sinf(DEG_TO_RAD(angle));
		//pos.x += moveSpeed * cosf(DEG_TO_RAD(angle));
		//pos.y -= moveSpeed * sinf(DEG_TO_RAD(angle));
	}

	if (target)
	{
		angle = GetAngle(pos, target->GetPos());

		pos.x += cosf(angle) * TimerManager::GetInstance()->GetDeltaTime() * 100;
		pos.y -= sinf(angle) * TimerManager::GetInstance()->GetDeltaTime() * 100;
	}
}

bool Missile::IsOutofScreen()
{
	float right = pos.x + size / 2;
	float left = pos.x - size / 2;
	float top = pos.y - size / 2;
	float bottom = pos.y + size / 2;

	if (right < 0 || left > WINSIZE_X
		|| bottom < 0 || top > WINSIZE_Y)
		return true;

	return false;
}

Missile::Missile()
{
}

Missile::~Missile()
{
}
