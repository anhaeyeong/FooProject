#pragma once
#include "GameObject.h"
#include "MissileFactory.h"

class Image;

class MissileFactory;
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
	int hp;
	float damage;
	string name;
	RECT rect;
	bool isAlive;

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
	void Dead();
	
	RECT GetRect() const { return rect; }
	inline float GetDamage() const { return damage; }
	inline int GetHP() const{ return hp; }
	inline FPOINT GetPos() const { return pos; }
	inline int GetSize() const { return size; }
	void ChangeAnimation(AnimationType anim);
	void ChangeState(State* newState);
	inline FPOINT GetPos() { return pos; }
	Rocket();
	~Rocket();
};

