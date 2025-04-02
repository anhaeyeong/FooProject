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

	image = ImageManager::GetInstance()->AddImage(
		"Normal_Enemy", TEXT("Image/MutaliskAnimation1.bmp"), 63, 70, 1, 1,
		true, RGB(255, 255, 255));
}

void Enemy::Move()
{
    // ���Ͽ� ���� �̵� ��� ó��
    switch (spawnPattern)
    {
    case 0:  // �Ϸķ� ���Ʒ��� �̵�
        pos.y += moveSpeed;
        if (pos.y > WINSIZE_Y - size) {
            moveSpeed = -abs(moveSpeed);
        }
        else if (pos.y < size) {
            moveSpeed = abs(moveSpeed);
        }
        break;

    case 1:  // ������ ��ġ�� �̵� (������ �̵� ������ �������� ����)
        pos.x += (rand() % 2 == 0 ? moveSpeed : -moveSpeed); // �¿�� �̵�
        pos.y += moveSpeed;
        if (pos.x > WINSIZE_X - size) pos.x = WINSIZE_X - size;
        if (pos.x < 0) pos.x = 0;
        if (pos.y > WINSIZE_Y - size) pos.y = WINSIZE_Y - size;
        break;

    case 2:  // ������� �̵�
        pos.x += (rand() % 2 == 0 ? moveSpeed : -moveSpeed); // �¿�� �̵�
        pos.y += moveSpeed;
        if (pos.x > WINSIZE_X - size || pos.x < 0) {
            moveSpeed = -moveSpeed; // ���� ������ ���� ����
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
	//UpdateCollisionRect();
}

void Enemy::Render(HDC hdc)
{
	if (isAlive)
	{
		image->Render(hdc, pos.x, pos.y, animationFrame);

	}
}

void Enemy::Move()
{
	pos.x += moveSpeed;
	if (pos.x > WINSIZE_X - 60) {
		moveSpeed = -abs(moveSpeed);
	}
	else if (pos.x < size)
	{
		moveSpeed = abs(moveSpeed);
	}
}

void Enemy::UpdateCollisionRect()
{
	rect = GetRectAtCenter(pos.x, pos.y, size, size);
}
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
