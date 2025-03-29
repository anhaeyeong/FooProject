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
	float damage;
	string name;
	RECT rcCollision;
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
	inline FPOINT GetPos() { return pos; }
	Rocket();
	~Rocket();
};

