#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"
#include "ColliderManager.h"

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
	if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}
}

void Enemy::Update()
{
	if (isAlive)
	{
		UpdateCollisionRect();
		eState->Update(*this);
	}

}

void Enemy::Render(HDC hdc)
{
	if (isAlive)
	{
		if(eState->GetName() == "IDLE")
			image->FrameRender(hdc, pos.x, pos.y, 0, animationFrame);
		if(eState->GetName() == "Dead")
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
	if (elapsedTime > 0.1f)
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
	moveSpeed = 0.4f;
	angle = -90.0f;
	isAlive = true;
	size = 30;
	animationFrame = 0;
	elapsedFrame = 0;
	elapsedTime = 0.0f;
}

void SmallEnemy::Move()
{
		pos.y += moveSpeed;
		if (pos.y > WINSIZE_Y - size) {
			moveSpeed = -abs(moveSpeed);
		}
		else if (pos.y < size) {
			moveSpeed = abs(moveSpeed);
		}
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
	moveSpeed = 0.4f;
	angle = -90.0f;
	isAlive = true;
	size = 30;
	animationFrame = 0;
	elapsedFrame = 0;
	elapsedTime = 0.0f;
}

void BigEnemy::Move()
{
		pos.x += (rand() % 2 == 0 ? moveSpeed : -moveSpeed);
		pos.y += moveSpeed;
		if (pos.x > WINSIZE_X - size) pos.x = WINSIZE_X - size;
		if (pos.x < 0) pos.x = 0;
		if (pos.y > WINSIZE_Y - size) pos.y = WINSIZE_Y - size;
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

void BossEnemy::Notice()
{
	moveSpeed = 0.4f;
	angle = -90.0f;
	isAlive = true;
	size = 30;
	animationFrame = 0;
	elapsedFrame = 0;
	elapsedTime = 0.0f;
}

void BossEnemy::Move()
{
	pos.x += (rand() % 2 == 0 ? moveSpeed : -moveSpeed);
	pos.y += moveSpeed;
	if (pos.x > WINSIZE_X - size) pos.x = WINSIZE_X - size;
	if (pos.x < 0) pos.x = 0;
	if (pos.y > WINSIZE_Y - size) pos.y = WINSIZE_Y - size;
}

void BossEnemy::Render(HDC hdc)
{
	if (isAlive)
	{
		image->FrameRender(hdc, pos.x, pos.y, 0, animationFrame);
	}
}

void BossEnemy::loadImage()
{
	ImageManager::GetInstance()->AddImage(
		"Normal_Enemy", TEXT("Image/MutaliskAnim.bmp"), 66, 365, 1, 5,
		true, RGB(255, 255, 255));
	ImageManager::GetInstance()->AddImage(
		"Normal_Enemy_Dead", TEXT("Image/MutaliskAnim.bmp"), 66, 365, 1, 5,
		true, RGB(255, 255, 255));
	image = ImageManager::GetInstance()->FindImage("Normal_Enemy");
	eState = new EnemyIDLEState();
}


//switch (spawnPattern)
//{
//case 0:
//	pos.y += moveSpeed;
//	if (pos.y > WINSIZE_Y - size) {
//		moveSpeed = -abs(moveSpeed);
//	}
//	else if (pos.y < size) {
//		moveSpeed = abs(moveSpeed);
//	}
//	break;
//
//case 1:
//	pos.x += (rand() % 2 == 0 ? moveSpeed : -moveSpeed);
//	pos.y += moveSpeed;
//	if (pos.x > WINSIZE_X - size) pos.x = WINSIZE_X - size;
//	if (pos.x < 0) pos.x = 0;
//	if (pos.y > WINSIZE_Y - size) pos.y = WINSIZE_Y - size;
//	break;
//
//case 2:
//	pos.x += (rand() % 2 == 0 ? moveSpeed : -moveSpeed);
//	pos.y += moveSpeed;
//	if (pos.x > WINSIZE_X - size || pos.x < 0) {
//		moveSpeed = -moveSpeed;
//	}
//	if (pos.y > WINSIZE_Y - size) pos.y = WINSIZE_Y - size;
//	break;
//}