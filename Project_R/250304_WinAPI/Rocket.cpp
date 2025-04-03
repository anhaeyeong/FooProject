#include "Rocket.h"
#include "CommonFunction.h"
#include "Image.h"
#include "InputManager.h"
#include "MissileFactory.h"
#include "State.h"
#include "ColliderManager.h"

void Rocket::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y - 100;

	size = 40;
	isAlive = true;

	canMove = true;

	hp = 3;
	ElapsedTime = 0.0f;
	HitTime = 0.0f;
	animationFrame = 0;

	missileFactory = PlayerMissileFactory::GetInstance();
	missileFactory->Init();
	ImageManager::GetInstance()->AddImage(
		"rocket", TEXT("Image/SCV_IDLE.bmp"), 35 * 2, 30 * 2, 1, 1, true, RGB(48, 64, 47));
	ImageManager::GetInstance()->AddImage(
		"MovingRocket", TEXT("Image/SCV_IDLE.bmp"), 35 * 2, 30 * 2, 1, 1,
		true, RGB(48, 64, 47));
	ImageManager::GetInstance()->AddImage(
		"AttackRocket", TEXT("Image/SCV_Attack.bmp"), 40 * 2, 41 * 2, 1, 1,
		true, RGB(48, 64, 47));
	ImageManager::GetInstance()->AddImage(
		"HitRocket", TEXT("Image/ufo.bmp"), 530, 32, 10, 1,
		true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(
		"DeadRocket", TEXT("Image/SCV_Dead.bmp"), 435, 97, 5, 1, true, RGB(255, 255, 255));
	image = ImageManager::GetInstance()->FindImage("rocket");
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
	/*HitTime += TimerManager::GetInstance()->GetDeltaTime();
	if (HitTime >= 2.0f)
	{
		hp--;
		HitTime = 0.0f;
	}*/
	
	missileFactory->Update();
	UpdateCollisionRect();
}

void Rocket::Render(HDC hdc)
{
	missileFactory->Render(hdc);
	if (isAlive)
	{
		image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0);
	}
}

void Rocket::Move()
{
	if (canMove = false) return;

	if (InputManager::isMoveLeft())
	{
		pos.x -= TimerManager::GetInstance()->GetDeltaTime() * 500;
	}

	if (InputManager::isMoveRight())
	{
		pos.x += TimerManager::GetInstance()->GetDeltaTime() * 500;
	}

	if (InputManager::isMoveUp())
	{
		pos.y -= TimerManager::GetInstance()->GetDeltaTime() * 500;
	}

	if (InputManager::isMoveDown()) {
		pos.y += TimerManager::GetInstance()->GetDeltaTime() * 500;
		if (!pos.y > WINSIZE_Y)
			pos.y = WINSIZE_Y - 100;
	}
}

void Rocket::HandleInput()
{
	if (state->GetName() == "Dead") return;
	if (InputManager::isMoveLeft())
	{
		if (state->GetName() != "Hit")
			ChangeState(new MovingState());
	}
	else if (InputManager::isMoveRight())
	{
		if (state->GetName() != "Hit")
			ChangeState(new MovingState());
	}
	else if (InputManager::isMoveUp())
	{
		if (state->GetName() != "Hit")
			ChangeState(new MovingState());
	}
	else if (InputManager::isMoveDown()) {
		if (state->GetName() != "Hit")
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
		if (state->GetName() != "Hit")
			ChangeState(new IDLEState());
	}

	if (InputManager::isFire())
	{
		ChangeState(new AttackState());
	}
	else if (KeyManager::GetInstance()->IsOnceKeyUp(VK_SPACE))
	{
		ChangeState(new IDLEState());
	}

	//CollisionManager
	/*if (CollisionManager::GetInstance()->OnCollision(this->GetRect()))
	{
		ChangeState(new HitState());
	}*/

	//Dead
	/*if (hp <= 0)
	{
		ChangeState(new DeadState());
	}*/
}

void Rocket::Fire()
{
	missileFactory->AddMissile(MissileType::LAZER, { pos.x, pos.y });
}

void Rocket::Hit()
{
	hp--;
}

void Rocket::Dead()
{
}

void Rocket::UpdateCollisionRect()
{
	rect = GetRectAtCenter(pos.x,pos.y, size, size);
}

void Rocket::UpdateAnimation(int maxFrame)
{
	ElapsedTime += TimerManager::GetInstance()->GetDeltaTime();
	if (ElapsedTime >= 0.2f)
	{
		animationFrame++;
		if (animationFrame >= maxFrame)
		{
			if (state->GetName() != "Dead")
				animationFrame = 0;
			else
			{
				if (animationFrame >= maxFrame + 10)
					isAlive = false;
			}
		}
		ElapsedTime = 0.0f;
	}
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
	if (state->GetName() == newState->GetName())
	{
		return;
	}
	if (state)
	{
		state->Exit(*this);
		delete state;
		state = newState;
		state->Enter(*this);
	}
}

string Rocket::GetState()
{
	return state->GetName();
}

Rocket::Rocket()
{
}

Rocket::~Rocket()
{
}