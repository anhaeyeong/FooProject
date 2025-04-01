#pragma once
#include "GameObject.h"
#include "MissileFactory.h"

class Image;
class MissileFactory;

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

	Image* image;
	MissileFactory* missileFactory;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void Move();
	void Fire();
	void Dead();
	
	RECT GetRect() const { return rect; }
	inline float GetDamage() const { return damage; }
	inline int GetHP() const{ return hp; }
	inline FPOINT GetPos() const { return pos; }
	Rocket();
	~Rocket();
};

