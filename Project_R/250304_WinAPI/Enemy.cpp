#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"

/*
	STL (Standard Template Library) : Vector
	동적배열을 제공하는 표준 템플릿 라이브러리 컨테이너
	배열과 흡사하지만 크기가 자동으로 조절된다.

	장점 : 임의접근 : 인덱스를 사용해서 O(1) 시간복잡도로
	원소에 접근이 가능하다.

	단점 : 배열과 같다. 중간에 원소를 삽입, 삭제 할 때 비용이
	시간복잡도 O(n) 가 많이 든다.
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


	image = ImageManager::GetInstance()->AddImage(
		"Normal_Enemy", TEXT("Image/ufo.bmp"), 530, 32, 10, 1,
		true, RGB(255, 0, 255));

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
