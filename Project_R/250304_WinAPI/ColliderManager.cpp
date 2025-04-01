#include "ColliderManager.h"
#include "CommonFunction.h"
#include "Rocket.h"
#include "Missile.h"
#include "Enemy.h"

void ColliderManager::Init()
{
	playerCollision.resize(50);
	enemyCollision.resize(50);
	missileCollision.resize(50);

	for (auto& p : playerCollision)
	{
		*p = GetRect(rocket->GetPos().x, rocket->GetPos().y, rocket->GetSize(), rocket->GetSize());
	}
	for (auto& e : enemyCollision)
	{
		*e = GetRect(enemy->GetPos().x, enemy->GetPos().y, enemy->GetSize(), enemy->GetSize());
	}
	for (auto& m : missileCollision)
	{
		*m = GetRect(missile->GetPos().x, missile->GetPos().y, missile->GetSize(), missile->GetSize());
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
	//충돌: 빨간색 , 충돌하지 않음: 초록색
	HPEN pen = CreatePen(PS_SOLID, 2, isCollision ? RGB(255, 0, 0) : RGB(0, 255, 0));

	HPEN oldPen = (HPEN)SelectObject(hdc, pen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

	for (auto& p : playerCollision)
	{
		Rectangle(hdc, p->left, p->top, p->right, p->bottom);
	}
	for (auto& e : enemyCollision)
	{
		Rectangle(hdc, e->left, e->top, e->right, e->bottom);
	}
	for (auto& m : missileCollision)
	{
		Rectangle(hdc, m->left, m->top, m->right, m->bottom);
	}

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



