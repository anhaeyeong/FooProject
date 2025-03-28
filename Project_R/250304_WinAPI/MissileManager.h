#pragma once
#include "GameObject.h"
#include <vector>

class Missile;
class MissileManager :public GameObject
{
private:
	vector<Missile*> vecMissiles;
	vector<Missile*>::iterator iterMissiles;

	vector<Missile*> EnemyMissiles;
	vector<Missile*>::iterator iterEnemyMissiles;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void Fire(FPOINT startPos, float angle);
	void EnemyFire(FPOINT StartPos, float angle);
};