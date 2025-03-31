#include "Rocket.h"
#include "CommonFunction.h"
#include "Image.h"
#include "InputManager.h"
#include "MissileManager.h"
#include "State.h"

void Rocket::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y - 100;

	size = 40;
	isAlive = true;

	missileManager = new MissileManager();
	missileManager->Init();

	image = ImageManager::GetInstance()->AddImage(
		"rocket", TEXT("Image/rocket.bmp"), 52, 64, true, RGB(255, 0, 255));

	state = new IDLEState();
	attackstate = nullptr;
}

void Rocket::Release()
{
	if (attackstate)
	{
		delete attackstate;
		attackstate = nullptr;
	}

	if (state)
	{
		delete state;
		state = nullptr;
	}
	
	if (missileManager)
	{
		missileManager->Release();
		delete missileManager;
		missileManager = nullptr;
	}
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

	if (missileManager)
	{
		missileManager->Update();
	}
}

void Rocket::Render(HDC hdc)
{
	if (isAlive)
	{
		image->Render(hdc, pos.x, pos.y);
	}

	missileManager->Render(hdc);

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
	missileManager->Fire({ pos.x,pos.y }, 90); // 플레이어 위치에서 위쪽으로 발사
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