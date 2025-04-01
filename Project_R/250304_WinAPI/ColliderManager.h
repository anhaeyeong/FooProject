#pragma once
#include "Singleton.h"
#include "GameObject.h"
#include <vector>

//충돌을 탐지해서 충돌검사 명령을 collider에게 내림 
//enum class MissileOwner { PLAYER, ENEMY };
//enum class MissileType { NORMAL, SIGN, LAZER };
//enum class ItemType {A, B, C};
class Missile;
class Rocket;
class Enemy;
class ColliderManager: public Singleton<ColliderManager>
{
private:
	vector<RECT*> playerCollision; //플레이어<->적, 플레이어 <-> 미사일
	vector<RECT*> enemyCollision; //적<->미사일 , 적 <-> 플레이어
	vector<RECT*> missileCollision; // 플레이어 미사일<-> 적, 적 미사일<-> 플레이어

	Missile* missileOwner; //getOwner로 적인지 플레이어인지 받음

	Missile* missile;
	Rocket* rocket;
	Enemy* enemy;

	bool isAlive;
	bool isCollision;

	MissileOwner owner;
	MissileType type;
	
public:
	
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	bool CheckCollision();
	void SetOwner();
	void isColliding(RECT* attacker, RECT* target);

	inline bool GetIsAlive() { return isAlive; }
	inline bool GetIsCollision() { return isCollision; }
};

