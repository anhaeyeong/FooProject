#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"

void Enemy::Init(float posX, float posY, int pattern)
{
    pos = { posX, posY };
    moveSpeed = 0.4f;
    isAlive = true;
    size = 30;
    animationFrame = 0;
    elapsedFrame = 0;
    spawnPattern = pattern;  // 패턴 초기화

    image = ImageManager::GetInstance()->AddImage(
        "Normal_Enemy", TEXT("Image/ufo.bmp"), 530, 32, 10, 1,
        true, RGB(255, 0, 255));
}

void Enemy::Move()
{
    // 패턴에 따른 이동 방식 처리
    switch (spawnPattern)
    {
    case 0:  // 일렬로 위아래로 이동
        pos.y += moveSpeed;
        if (pos.y > WINSIZE_Y - size) {
            moveSpeed = -abs(moveSpeed);
        }
        else if (pos.y < size) {
            moveSpeed = abs(moveSpeed);
        }
        break;

    case 1:  // 랜덤한 위치로 이동 (간단히 이동 방향을 무작위로 설정)
        pos.x += (rand() % 2 == 0 ? moveSpeed : -moveSpeed); // 좌우로 이동
        pos.y += moveSpeed;
        if (pos.x > WINSIZE_X - size) pos.x = WINSIZE_X - size;
        if (pos.x < 0) pos.x = 0;
        if (pos.y > WINSIZE_Y - size) pos.y = WINSIZE_Y - size;
        break;

    case 2:  // 지그재그 이동
        pos.x += (rand() % 2 == 0 ? moveSpeed : -moveSpeed); // 좌우로 이동
        pos.y += moveSpeed;
        if (pos.x > WINSIZE_X - size || pos.x < 0) {
            moveSpeed = -moveSpeed; // 벽에 닿으면 방향 반전
        }
        if (pos.y > WINSIZE_Y - size) pos.y = WINSIZE_Y - size;
        break;
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
		Move();


		elapsedFrame++;
		if (elapsedFrame > 5)
		{
			animationFrame++;
			if (animationFrame >= image->GetMaxFrameX())
			{
				animationFrame = 0;
			}
			elapsedFrame = 0;
		}
	}

}

void Enemy::Render(HDC hdc)
{
	if (isAlive)
	{
		image->Render(hdc, pos.x, pos.y, animationFrame);

	}
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
