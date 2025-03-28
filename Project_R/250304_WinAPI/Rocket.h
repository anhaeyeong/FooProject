#pragma once
#include "GameObject.h"

class Image;
class MissileManager;
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
	MissileManager* missileManager;

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

