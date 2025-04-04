#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"
#include "ColliderManager.h"
#include "Rocket.h"
#include "MissileFactory.h"

void Enemy::Init(float posX, float posY, int pattern)
{
	pos = { posX, posY };
	moveSpeed = 0.4f;
	angle = -90.0f;
	isAlive = true;
	size = 30;
	hp = 1;
	animationFrame = 0;
	elapsedFrame = 0;
	spawnPattern = pattern;
	elapsedTime = 0.0f;

	missileFactory = EnemyMissileFactory::GetInstance();
	missileFactory->Init();

	ImageManager::GetInstance()->AddImage(
		"Normal_Enemy", TEXT("Image/MutaliskAnim.bmp"), 66, 365, 1, 5,
		true, RGB(255, 255, 255));
	ImageManager::GetInstance()->AddImage(
		"Normal_Enemy_Dead", TEXT("Image/MutaliskDeadAnim.bmp"), 621, 62, 9, 1,
		true, RGB(255, 255, 255));
	image = ImageManager::GetInstance()->FindImage("Normal_Enemy");
	eState = new EnemyIDLEState();
}

void Enemy::Move()
{
	pos.y += moveSpeed;
	if (pos.y > WINSIZE_Y - size) {
		moveSpeed = -abs(moveSpeed);
	}
	else if (pos.y < size) {
		moveSpeed = abs(moveSpeed);
	}
}

void Enemy::ChangeState(EnemyState* newState)
{
	if (eState->GetName() == newState->GetName())
	{
		return;
	}
	if (eState)
	{
		eState->Exit(*this);
		delete eState;
		eState = newState;
		eState->Enter(*this);
	}
}

void Enemy::SetPosition(float newX, float newY)
{
	pos.x = newX;
	pos.y = newY;
}

void Enemy::Release()
{
	missileFactory->Release();

	if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}
}

void Enemy::Update()
{
	missileFactory->Update();
	if (isAlive)
	{
		UpdateCollisionRect();
		eState->Update(*this);
	}

}

void Enemy::Render(HDC hdc)
{
	missileFactory->Render(hdc);
	if (isAlive)
	{
		if (eState->GetName() == "IDLE")
			image->FrameRender(hdc, pos.x, pos.y, 0, animationFrame);
		if (eState->GetName() == "Dead")
			image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0);
	}
}

void Enemy::UpdateCollisionRect()
{
	rect = GetRectAtCenter(pos.x, pos.y, size, size);
}

void Enemy::UpdateAnimation(int maxFrame)
{
	elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
	if (elapsedTime > 0.05f)
	{
		animationFrame++;
		if (animationFrame >= maxFrame)
		{
			if (eState->GetName() != "Dead")
			{
				animationFrame = 0;
			}
			else
			{
				isAlive = false;
			}
		}
		elapsedTime = 0.0f;
	}
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void SmallEnemy::ChangeAnimation(EnemyAnimType eAnimation)
{
	switch (eAnimation)
	{
	case EnemyAnimType::EIDLE:
		image = ImageManager::GetInstance()->FindImage("Normal_Enemy");
		break;
	case EnemyAnimType::EDead:
		image = ImageManager::GetInstance()->FindImage("Normal_Enemy_Dead");
		break;
	}
}

void SmallEnemy::Notice()
{
	moveSpeed = 0.2f;
	angle = -90.0f;
	size = 40;
}

void SmallEnemy::Move()
{
	pos.y += moveSpeed * TimerManager::GetInstance()->GetDeltaTime() * 500;
}

void SmallEnemy::Render(HDC hdc)
{
	if (isAlive)
	{
		if (eState->GetName() == "IDLE")
			image->FrameRender(hdc, pos.x, pos.y, 0, animationFrame);
		if (eState->GetName() == "Dead")
			image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0);
	}
}

void SmallEnemy::loadImage()
{
	ImageManager::GetInstance()->AddImage(
		"Normal_Enemy", TEXT("Image/MutaliskAnim.bmp"), 66, 365, 1, 5,
		true, RGB(255, 255, 255));
	ImageManager::GetInstance()->AddImage(
		"Normal_Enemy_Dead", TEXT("Image/MutaliskDeadAnim.bmp"), 621, 62, 9, 1,
		true, RGB(255, 255, 255));
	image = ImageManager::GetInstance()->FindImage("Normal_Enemy");
	eState = new EnemyIDLEState();
}

void BigEnemy::ChangeAnimation(EnemyAnimType eAnimation)
{
	switch (eAnimation)
	{
	case EnemyAnimType::EIDLE:
		image = ImageManager::GetInstance()->FindImage("Big_Enemy");
		break;
	case EnemyAnimType::EDead:
		image = ImageManager::GetInstance()->FindImage("Big_enemy_Dead");
		break;
	}
}

void BigEnemy::Notice()
{
	moveSpeed = 0.2f;
	angle = -90.0f;
	size = 50;
}

void BigEnemy::Move()
{
	pos.x += (rand() % 2 == 0 ? moveSpeed : -moveSpeed) * TimerManager::GetInstance()->GetDeltaTime() * 500;
	pos.y += moveSpeed * TimerManager::GetInstance()->GetDeltaTime() * 500;
}

void BigEnemy::Render(HDC hdc)
{
	if (isAlive)
	{
		if (eState->GetName() == "IDLE")
			image->FrameRender(hdc, pos.x, pos.y, 0, animationFrame);
		if (eState->GetName() == "Dead")
			image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0);
	}
}

void BigEnemy::loadImage()
{
	ImageManager::GetInstance()->AddImage(
		"Big_Enemy", TEXT("Image/GuardianAnimation.bmp"), 80, 504, 1, 7,
		true, RGB(255, 255, 255));
	ImageManager::GetInstance()->AddImage(
		"Big_enemy_Dead", TEXT("Image/GuardianDeadAnim.bmp"), 1035, 112, 9, 1,
		true, RGB(255, 255, 255));
	image = ImageManager::GetInstance()->FindImage("Big_Enemy");
	eState = new EnemyIDLEState();
}


void BossEnemy::ChangeAnimation(EnemyAnimType eAnimation)
{
	switch (eAnimation)
	{
	case EnemyAnimType::EIDLE:
		image = ImageManager::GetInstance()->FindImage("Boss_Enemy");
		break;
	case EnemyAnimType::EDead:
		image = ImageManager::GetInstance()->FindImage("Boss_enemy_Dead");
		break;
	}
}

void BossEnemy::CalcAttackPattern()
{
	attackpattern = rand() % 4;
	switch (attackpattern)
	{
	case 0:
		missileFactory->AddMissile(MissileType::NORMAL, { pos.x, 120 });
		break;
	case 1:
		missileFactory->AddMissile(MissileType::SIGN, { pos.x, 120 });
		break;
	case 2:
		missileFactory->AddMissile(MissileType::LAZER, { pos.x, 120 });
		break;
	case 3:
		for (int i = 0; i < 4; i++)
		{
			missileFactory->AddMissile(MissileType::BOSS, { pos.x, 120 });
		}
		break;
	default:
		break;
	}
}

void BossEnemy::Notice()
{
	moveSpeed = 200.0f;
	angle = -90.0f;
	size = 300;
}

void BossEnemy::Move()
{
	cooltime -= TimerManager::GetInstance()->GetDeltaTime();
	if (cooltime <= 0.0f)
	{
		CalcAttackPattern();
		cooltime = 0.7f;
	}
	Lazercooltime -= TimerManager::GetInstance()->GetDeltaTime();
	if (Lazercooltime <= 0.0f)
	{
		missileFactory->AddMissile(MissileType::LAZER, { 0  , 0 });
		missileFactory->AddMissile(MissileType::LAZER, { WINSIZE_X  , 0 });
		missileFactory->AddMissile(MissileType::LAZER, { 50  , 0 });
		missileFactory->AddMissile(MissileType::LAZER, { WINSIZE_X - 50  , 0 });
		missileFactory->AddMissile(MissileType::LAZER, { 100  , 0 });
		missileFactory->AddMissile(MissileType::LAZER, { WINSIZE_X - 100  , 0 });
		Lazercooltime = 0.3f;
	}
	int randSpeed = rand() % 200 + 150;
	moveSpeed = (float)randSpeed;
	pos.x += TimerManager::GetInstance()->GetDeltaTime() * moveSpeed * dir;
	if (pos.x > WINSIZE_X - 300)
	{
		dir = -1;
	}
	else if (pos.x < 300)
	{
		dir = 1;
	}
}

void BossEnemy::Render(HDC hdc)
{
	if (isAlive)
	{
		image->FrameRender(hdc, pos.x, pos.y, animationFrame * 4 / 5, 0);
	}
}

void BossEnemy::loadImage()
{
	ImageManager::GetInstance()->AddImage(
		"Boss_Enemy", TEXT("Image/OverMind_faze1.bmp"), 832 * 1.5, 136 * 1.5, 4, 1,
		true, RGB(35, 35, 255));
	ImageManager::GetInstance()->AddImage(
		"Boss_enemy_Dead", TEXT("Image/MutaliskDeadAnim.bmp"), 621 * 5, 62 * 5, 9, 1,
		true, RGB(255, 255, 255));
	image = ImageManager::GetInstance()->FindImage("Boss_Enemy");
	eState = new EnemyIDLEState();
}

void TrackingEnemy::ChangeAnimation(EnemyAnimType eAnimation)
{
	switch (eAnimation)
	{
	case EnemyAnimType::EIDLE:
		image = ImageManager::GetInstance()->FindImage("Tracking_Enemy");
		break;
	case EnemyAnimType::EDead:
		image = ImageManager::GetInstance()->FindImage("Tracking_Enemy_Dead");
		break;
	}
}

void TrackingEnemy::Notice()
{
	moveSpeed = 150.0f;
	angle = 0.0f;
	isAlive = true;
	size = 20;
	hp = 1;  
	trackingSpeed = 400.0f;
	detectRange = 900.0f;  
	animationFrame = 0;
	elapsedFrame = 0;
	elapsedTime = 0.0f;
}

void TrackingEnemy::Move()
{
	Rocket* rocket = ColliderManager::GetInstance()->GetRocket();
	if (rocket && rocket->GetIsAlive())
	{
		FPOINT playerPos = rocket->GetPos();
		TrackPlayer(playerPos);
	}
	else
	{
		pos.y += moveSpeed * TimerManager::GetInstance()->GetDeltaTime();

		if (pos.x > WINSIZE_X - size)
		{
			pos.x = WINSIZE_X - size;
		}
		else if (pos.x < 0)
		{
			pos.x = 0;
		}
		else if (pos.y > WINSIZE_Y - size)
		{
			pos.y = WINSIZE_Y - size;
		}
		else if (pos.y < 0)
		{
			pos.y = 0;
		}
	}
}

void TrackingEnemy::TrackPlayer(const FPOINT& playerPos)
{
	float dx = playerPos.x - pos.x;
	float dy = playerPos.y - pos.y;
	float distance = sqrt(dx * dx + dy * dy);

	if (distance < detectRange)
	{
		float dirX = (distance > 0) ? dx / distance : 0;
		float dirY = (distance > 0) ? dy / distance : 0;

		float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
		pos.x += dirX * trackingSpeed * deltaTime;
		pos.y += dirY * trackingSpeed * deltaTime;

		UpdateAnimation(5);
	}
	else
	{
		pos.y += moveSpeed * TimerManager::GetInstance()->GetDeltaTime();
		UpdateAnimation(5);
	}

	if (pos.x > WINSIZE_X - size) pos.x = WINSIZE_X - size;
	if (pos.x < 0) pos.x = 0;
	if (pos.y > WINSIZE_Y - size) pos.y = WINSIZE_Y - size;
	if (pos.y < 0) pos.y = 0;
}

void TrackingEnemy::Render(HDC hdc)
{
	if (isAlive)
	{
		if (eState->GetName() == "IDLE")
			image->FrameRender(hdc, pos.x, pos.y, 0, animationFrame);
		else if (eState->GetName() == "Dead")
			image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0);
	}
}

void TrackingEnemy::loadImage()
{
	ImageManager::GetInstance()->AddImage(
		"Tracking_Enemy", TEXT("Image/ScurgeAnimation.bmp"), 33, 140, 1, 5,
		true, RGB(255, 255, 255));
	ImageManager::GetInstance()->AddImage(
		"Tracking_Enemy_Dead", TEXT("Image/ScurgeDeadAnim.bmp"), 621, 62, 9, 1,
		true, RGB(255, 255, 255));

	image = ImageManager::GetInstance()->FindImage("Tracking_Enemy");
	eState = new EnemyIDLEState();
}