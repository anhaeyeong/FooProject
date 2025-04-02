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
	animationFrame = 0;
	elapsedFrame = 0;
	spawnPattern = pattern;
	elapsedTime = 0.0f;

	ImageManager::GetInstance()->AddImage(
		"Normal_Enemy", TEXT("Image/MutaliskAnim.bmp"), 66, 365, 1, 5,
		true, RGB(255, 255, 255));
	ImageManager::GetInstance()->AddImage(
		"Normal_Enemy_Dead", TEXT("Image/MutaliskAnim.bmp"), 66, 365, 1, 5,
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

void Enemy::ChangeAnimation(EnemyAnimType eAnimation)
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
		image->FrameRender(hdc, pos.x, pos.y, 0, animationFrame);
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
				animationFrame = 0;
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
		image->FrameRender(hdc, pos.x, pos.y, 0, animationFrame);
	}
}

void SmallEnemy::loadImage()
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
		image->FrameRender(hdc, pos.x, pos.y, 0, animationFrame);
	}
}

void BigEnemy::loadImage()
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