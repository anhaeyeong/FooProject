#pragma once
#include "GameObject.h"
#include "ImageManager.h"
#include "EnemyState.h"

enum EnemyAnimType
{
	EIDLE,
	EDead
};
class MissileFactory;
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
	string name;

	MissileFactory* missileFactory;
	Image* image;
	RECT rect;
	EnemyState* eState;

public:
	Enemy();
	virtual ~Enemy();

	string GetName() const { return name; }

	void SetPosition(float newX, float newY);

	void Init(float posX, float posY, int pattern = 0);
	void Release();
	void Update();
	virtual void ChangeAnimation(EnemyAnimType eAnimation) = 0;
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
	EnemyState* GetState() const { return eState; }

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

	void ChangeAnimation(EnemyAnimType eAnimation) override;

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

	void ChangeAnimation(EnemyAnimType eAnimation) override;

	virtual void Notice() override;
	virtual void Move() override;
	virtual void Render(HDC hdc) override;
	virtual void loadImage() override;
};

class BossEnemy : public Enemy
{
private:
	float cooltime;
	float Lazercooltime;
	int attackpattern;
	int dir;
public:
	BossEnemy() : Enemy(), cooltime(0.0f), Lazercooltime(0.0f), attackpattern(0), dir(1) {}
	virtual ~BossEnemy() {}

	void ChangeAnimation(EnemyAnimType eAnimation) override;
	void CalcAttackPattern();

	virtual void Notice() override;
	virtual void Move() override;
	virtual void Render(HDC hdc) override;
	virtual void loadImage() override;
};

class TrackingEnemy : public Enemy
{
private:
	float trackingSpeed;   // 추적 속도
	float detectRange;     // 감지 범위

public:
	TrackingEnemy() : Enemy() {}
	virtual ~TrackingEnemy() {}

	void ChangeAnimation(EnemyAnimType eAnimation) override;
	virtual void Notice() override;
	virtual void Move() override;
	virtual void Render(HDC hdc) override;
	virtual void loadImage() override;

	// 플레이어 추적 로직
	void TrackPlayer(const FPOINT& playerPos);
};