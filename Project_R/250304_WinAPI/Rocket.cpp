#include "Rocket.h"
#include "CommonFunction.h"
#include "Image.h"
#include "InputManager.h"

void Rocket::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y - 100;

	size = 40;
	isAlive = true;

	image = ImageManager::GetInstance()->AddImage(
		"rocket", TEXT("Image/rocket.bmp"), 52, 64, true, RGB(255, 0, 255));

	missileFactory = PlayerMissileFactory::GetInstance();
	missileFactory->Init();
}

void Rocket::Release()
{
	missileFactory->Release();
}

void Rocket::Update()
{
	if (isAlive)
	{
		Move();
	}

	if (InputManager::isFire())
	{
		Fire();
	}

	missileFactory->Update();
}

void Rocket::Render(HDC hdc)
{
	if (isAlive)
	{
		image->Render(hdc, pos.x, pos.y);
		missileFactory->Render(hdc);
	}
}

void Rocket::Move()
{
	if (InputManager::isMoveLeft())
		pos.x -= TimerManager::GetInstance()->GetDeltaTime() * 100;
	if (InputManager::isMoveRight())
		pos.x += TimerManager::GetInstance()->GetDeltaTime() * 100;
	if (InputManager::isMoveUp())
		pos.y -= TimerManager::GetInstance()->GetDeltaTime() * 100;
	if (InputManager::isMoveDown()) {
		pos.y += TimerManager::GetInstance()->GetDeltaTime() * 100;
		if (!pos.y > WINSIZE_Y)
			pos.y = WINSIZE_Y - 100;
	}
}

void Rocket::Fire()
{
	missileFactory->AddMissile(MissileType::NORMAL);
}

void Rocket::Dead()
{
}

Rocket::Rocket()
{
}

Rocket::~Rocket()
{
}