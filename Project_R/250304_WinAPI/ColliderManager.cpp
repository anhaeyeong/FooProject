#include "ColliderManager.h"
#include "CommonFunction.h"
#include "Rocket.h"
#include "Missile.h"
#include "Enemy.h"

void ColliderManager::Init()
{
	for (auto& p : playerCollision)
	{
		*p = rocket->GetRect();
	}
	for (auto& e : enemyCollision)
	{
		*e = enemy->GetRect();
	}
	for (auto& m : missileCollision)
	{
		*m = missile->GetRect();
	}
}

void ColliderManager::Release()
{
	for (auto& p : playerCollision)
	{
		delete p;
		p = nullptr;
	}
	playerCollision.clear();
	for (auto& e : enemyCollision)
	{
		delete e;
		e = nullptr;
	}
	enemyCollision.clear();
	for (auto& m : missileCollision)
	{
		delete m;
		m = nullptr;
	}
	missileCollision.clear();
}

void ColliderManager::Update()
{
	CheckCollision();
}

void ColliderManager::Render(HDC hdc)
{
	
	HPEN pen = CreatePen(PS_SOLID, 2, isCollision ? RGB(255, 0, 0) : RGB(0, 255, 0));

	HPEN oldPen = (HPEN)SelectObject(hdc, pen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

	Rectangle(hdc, enemy->GetRect().left, enemy->GetRect().top, enemy->GetRect().right, enemy->GetRect().bottom);
	Rectangle(hdc, missile->GetRect().left, missile->GetRect().top, missile->GetRect().right, missile->GetRect().bottom);
	Rectangle(hdc, rocket->GetRect().left, rocket->GetRect().top, rocket->GetRect().right, rocket->GetRect().bottom);

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
	DeleteObject(pen);

}

bool ColliderManager::CheckCollision()
{
	SetOwner();

	if (owner == MissileOwner::PLAYER && type == MissileType::LAZER)
	{
		for (auto& p : playerCollision)
		{
			for (auto& m : missileCollision)
			{
				isColliding(p, m);
				return RectInRect(*p,*m);
			}
		}
	}
	else if (owner == MissileOwner::PLAYER && type == MissileType::NORMAL)
	{
		for (auto& p : playerCollision)
		{
			for (auto& m : missileCollision)
			{
				isColliding(p, m);
				return RectInRect(*p, *m);
			}
		}
	}
	else if (owner == MissileOwner::PLAYER && type == MissileType::SIGN)
	{
		for (auto& p : playerCollision)
		{
			for (auto& m : missileCollision)
			{
				isColliding(p, m);
				return RectInRect(*p, *m);
			}
		}
	}
	else if (owner == MissileOwner::ENEMY && type == MissileType::NORMAL)
	{
		for (auto& e : enemyCollision)
		{
			for (auto& m : missileCollision)
			{
				isColliding(e, m);
				return RectInRect(*e, *m);
			}
		}
	}
}

void ColliderManager::SetOwner()
{
	owner = missileOwner->GetOwner();
	type = missileOwner->GetType();
}

void ColliderManager::isColliding(RECT* attacker, RECT* target)
{
	if (attacker == nullptr || target == nullptr) return;

	// 두 충돌 영역이 유효한지 확인
	if (attacker->left != target->right &&
		attacker->top != target->bottom &&
		target->left != attacker->right &&
		target->top != attacker->bottom)
	{
		if (RectInRect(*attacker, *target))
		{
			isCollision = true;
			isAlive = false;
		}
		else
		{
			isCollision = false;
		}
	}
}



