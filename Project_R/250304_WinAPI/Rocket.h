#pragma once
#include "GameObject.h"

class Image;
class MissileManager;
class State;
class AttackState;

enum class AnimationType
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
	float damage;
	string name;
	RECT rcCollision;
	bool isAlive;

	State* state;
	Image* image;
	MissileManager* missileManager;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void Move();
	void HandleInput();
	void Fire();
	void Dead();
	void ChangeAnimation(AnimationType anim);
	void ChangeState(State* newState);
	inline FPOINT GetPos() { return pos; }
	Rocket();
	~Rocket();
};

