#pragma once
#include "GameObject.h"
#include "ImageManager.h"

class Enemy : public GameObject
{
private:

	FPOINT pos;
	float moveSpeed;		//5.0f
	float angle;
	float damage;
	bool isAlive;
	int size;
	Image* image;
	int spawnPattern;
	int animationFrame;
	int elapsedFrame;
	float elapsedTime;
	int hp;
	RECT rect;

public:
    void Init(float posX, float posY, int pattern = 0);
    void Release();
    void Update();
    void Render(HDC hdc);

    void Move();

	void UpdateCollisionRect();
	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() {	return isAlive;	}
	RECT GetRect() const { return rect; }
	inline void SetTarget(Tank* target) { this->target = target; }
	inline FPOINT GetPos() { return pos; }
	inline int GetSize() { return size; }
	inline int GetHP() const { return hp; }
	inline float GetDamage() const { return damage; }
	inline RECT GetRectAtCenter(int x, int y, int width, int height)
	{
		RECT rc{ x - (width / 2), y - (height / 2),
			x + (width / 2), y + (height / 2) };
		return rc;
	}
	Enemy();
	~Enemy();
};
