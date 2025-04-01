#include "Rocket.h"
#include "CommonFunction.h"
#include "Image.h"
#include "InputManager.h"
#include "MissileFactory.h"
#include "State.h"


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

	ImageManager::GetInstance()->AddImage(
		"rocket", TEXT("Image/rocket.bmp"), 52, 64, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(
		"MovingRocket", TEXT("Image/ufo.bmp"), 530, 32, 10, 1,
		true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(
		"AttackRocket", TEXT("Image/ufo.bmp"), 530, 32, 10, 1,
		true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(
		"HitRocket", TEXT("Image/ufo.bmp"), 530, 32, 10, 1,
		true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(
		"DeadRocket", TEXT("Image/rocket.bmp"), 52, 64, true, RGB(255, 0, 255));
	image = ImageManager::GetInstance()->FindImage("HitRocket");
	state = new IDLEState();
}

void Rocket::Release()
{

	missileFactory->Release();


	if (state)
	{
		delete state;
		state = nullptr;
	}

}

void Rocket::Update()
{
	HandleInput();
	if (isAlive && state)
	{
		state->Update(*this);
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
	{
		pos.x -= TimerManager::GetInstance()->GetDeltaTime() * 100;
	}
		
	if (InputManager::isMoveRight())
	{
		pos.x += TimerManager::GetInstance()->GetDeltaTime() * 100;
	}
		
	if (InputManager::isMoveUp())
	{
		pos.y -= TimerManager::GetInstance()->GetDeltaTime() * 100;
	}
		
	if (InputManager::isMoveDown()) {
		pos.y += TimerManager::GetInstance()->GetDeltaTime() * 100;
		if (!pos.y > WINSIZE_Y)
			pos.y = WINSIZE_Y - 100;
	}
}

void Rocket::HandleInput()
{
	if (InputManager::isMoveLeft())
	{
		if(state->GetName() != "Moving")
			ChangeState(new MovingState());
	}

	if (InputManager::isMoveRight())
	{
		if (state->GetName() != "Moving")
			ChangeState(new MovingState());
	}

	if (InputManager::isMoveUp())
	{
		if (state->GetName() != "Moving")
			ChangeState(new MovingState());
	}

	if (InputManager::isMoveDown()) {
		if (state->GetName() != "Moving")
			ChangeState(new MovingState());
		if (!pos.y > WINSIZE_Y)
			pos.y = WINSIZE_Y - 100;
	}
	if (KeyManager::GetInstance()->IsOnceKeyUp(VK_NUMPAD4) ||
		KeyManager::GetInstance()->IsOnceKeyUp(VK_NUMPAD5) ||
		KeyManager::GetInstance()->IsOnceKeyUp(VK_NUMPAD6) ||
		KeyManager::GetInstance()->IsOnceKeyUp(VK_NUMPAD8) ||
		KeyManager::GetInstance()->IsOnceKeyUp(VK_SPACE))
	{
		ChangeState(new IDLEState());
	}
	if (InputManager::isFire())
	{
		ChangeState(new AttackState());
	}
	if (KeyManager::GetInstance()->IsOnceKeyUp(VK_SPACE))
	{
		ChangeState(new IDLEState());
	}
}

void Rocket::Fire()
{
	missileFactory->AddMissile(MissileType::NORMAL);
}

void Rocket::Dead()
{
}

void Rocket::ChangeAnimation(AnimationType anim)
{
	switch (anim)
	{
	case AnimationType::IDLE:
		image = ImageManager::GetInstance()->FindImage("rocket");
		break;
	case AnimationType::Moving:
		image = ImageManager::GetInstance()->FindImage("MovingRocket");
		break;
	case AnimationType::Attack:
		image = ImageManager::GetInstance()->FindImage("AttackRocket");
		break;
	case AnimationType::Hit:
		image = ImageManager::GetInstance()->FindImage("HitRocket");
		break;
	case AnimationType::Dead:
		image = ImageManager::GetInstance()->FindImage("DeadRocket");
		break;
	}
}

void Rocket::ChangeState(State* newState)
{
	if (state)
	{
		state->Exit(*this);
		delete state;
		state = newState;
		state->Enter(*this);
	}
}

Rocket::Rocket()
{
}

Rocket::~Rocket()
{
}