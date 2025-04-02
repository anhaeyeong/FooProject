#pragma once
#include "GameObject.h"
#include "ImageManager.h"
#include "EnemyState.h"

enum EnemyAnimType
{
	EIDLE,
	EDead
};

class Enemy : public GameObject
{
protected:
	FPOINT pos;
	float moveSpeed;
	float angle;
	float damage;
	int size;
	int hp;
	bool isAlive;
	int spawnPattern;
	int animationFrame;
	int elapsedFrame;
	float elapsedTime;
	Image* image;
	RECT rect;
	EnemyState* eState;

public:
	Enemy();
	virtual ~Enemy();

	void Init(float posX, float posY, int pattern = 0);
	void Release();
	void Update();
	void ChangeAnimation(EnemyAnimType eAnimation);
	void ChangeState(EnemyState* newState);

	virtual void Notice() = 0;
	virtual void Move() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void loadImage() = 0;

	void UpdateCollisionRect();
	void UpdateAnimation(int maxFrame);

	void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	bool GetIsAlive() const { return isAlive; }
	RECT GetRect() const { return rect; }
	FPOINT GetPos() const { return pos; }
	int GetSize() const { return size; }
	int GetHP() const { return hp; }
	float GetDamage() const { return damage; }

	static RECT GetRectAtCenter(int x, int y, int width, int height)
	{
		RECT rc{ x - (width / 2), y - (height / 2),
				 x + (width / 2), y + (height / 2) };
		return rc;
	}
};

class SmallEnemy : public Enemy
{
public:
	SmallEnemy() : Enemy() {}
	virtual ~SmallEnemy() {}

	virtual void Notice() override;
	virtual void Move() override;
	virtual void Render(HDC hdc) override;
	virtual void loadImage() override;
};

class BigEnemy : public Enemy
{
public:
	BigEnemy() : Enemy() {}
	virtual ~BigEnemy() {}

	virtual void Notice() override;
	virtual void Move() override;
	virtual void Render(HDC hdc) override;
	virtual void loadImage() override;
};

class BossEnemy : public Enemy
{
public:
	BossEnemy() : Enemy() {}
	virtual ~BossEnemy() {}

	virtual void Notice() override;
	virtual void Move() override;
	virtual void Render(HDC hdc) override;
	virtual void loadImage() override;
};
