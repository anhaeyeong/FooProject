#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"

/*
	STL (Standard Template Library) : Vector
	�����迭�� �����ϴ� ǥ�� ���ø� ���̺귯�� �����̳�
	�迭�� ��������� ũ�Ⱑ �ڵ����� �����ȴ�.

	���� : �������� : �ε����� ����ؼ� O(1) �ð����⵵��
	���ҿ� ������ �����ϴ�.

	���� : �迭�� ����. �߰��� ���Ҹ� ����, ���� �� �� �����
	�ð����⵵ O(n) �� ���� ���.
*/

void Enemy::Init(float posX, float posY)
{
	pos = { posX, posY };
	moveSpeed = 0.4f;
	angle = -90.0f;
	isAlive = true;
	size = 30;
	animationFrame = 0;
	elapsedFrame = 0;
	elapsedTime = 0.0f;

	image = ImageManager::GetInstance()->AddImage(
		"Normal_Enemy", TEXT("Image/MutaliskAnim.bmp"), 66, 365, 1, 5,
		true, RGB(255, 255, 255));

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
		elapsedTime += TimerManager::GetInstance()->GetDeltaTime();

		if (elapsedTime > 0.1f)
		{
			animationFrame++;
			if (animationFrame >= image->GetMaxFrameY())
			{
				animationFrame = 0;
			}
			elapsedTime = 0.0f;
		}
	}

}

void Enemy::Render(HDC hdc)
{
	if (isAlive)
	{
		image->FrameRender(hdc, pos.x, pos.y, 0, animationFrame);

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

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
