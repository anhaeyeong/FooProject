#pragma once
#include "GameObject.h"
#include "MissileFactory.h"

class Image;

class MissileFactory;
class MissileManager;
class State;
class AttackState;

enum AnimationType
{
	IDLE,
	Moving,
	Attack,
	Hit,
	Dead
};

class Rocket : public GameObject
{
private:
	FPOINT pos;
	int size;
	int hp;
	float damage;
	float angle;
	string name;
	RECT rect;
	bool isAlive;

	bool canMove;

	float ElapsedTime;
	float HitTime;
	int animationFrame;
	MissileType currMissile;

	State* state;
	Image* image;
	MissileFactory* missileFactory;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void Move();
	void HandleInput();
	void Fire();
	void Hit();
	void Dead();

	void UpdateCollisionRect();
	void UpdateAnimation(int maxFrame);
	
	void SetCanMove(bool can) { canMove = can; }
	bool GetCanMove() const { return canMove; }
	RECT GetRect() const { return rect; }
	inline float GetDamage() const { return damage; }
	inline int GetHP() const{ return hp; }
	inline FPOINT GetPos() const { return pos; }
	inline int GetSize() const { return size; }
	void ChangeAnimation(AnimationType anim);
	void ChangeState(State* newState);
	void ChangeMissile(MissileType newMissileType);
	inline FPOINT GetPos() { return pos; }
	inline RECT GetRectAtCenter(int x, int y, int width, int height)
	{
		RECT rc{ x - (width / 2), y - (height / 2),
			x + (width / 2), y + (height / 2) };
		return rc;
	}
	inline bool GetIsAlive() { return isAlive; }
	string GetState();
	void ChangeMissileType(MissileType newType);
	// ���� �̻��� Ÿ�� ��������
	MissileType GetCurrentMissileType() const { return currentMissileType; }
	Rocket();
	~Rocket();
};

