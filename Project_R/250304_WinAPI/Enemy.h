#pragma once
#include "GameObject.h"
#include "ImageManager.h"

class Tank;
class Image;

class Enemy : public GameObject	// is-a
{
private:
	FPOINT pos;
	float moveSpeed;		//5.0f 1프레임당 이동거리    물리에서의 속도 = 시간당 이동거리
	float angle;
	float damage;
	bool isAlive;
	int size;
	Tank* target;
	Image* image;
	int animationFrame;
	int elapsedFrame;
	float elapsedTime;
	int hp;
	RECT rect;

public:
	void Init(float posX = 0.0f, float posY = 0.0f);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();

	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() {	return isAlive;	}
	RECT GetRect() const { return rect; }
	inline void SetTarget(Tank* target) { this->target = target; }
	inline FPOINT GetPos() { return pos; }
	inline int GetSize() { return size; }
	inline int GetHP() const { return hp; }
	inline float GetDamage() const { return damage; }
	Enemy();
	~Enemy();
};

