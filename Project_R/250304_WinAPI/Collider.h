#pragma once
#include "GameObject.h"
//충돌 : 적 미사일(원)       - 플레이어 (원)
//		 적 개체(원)         - 플레이어 (원)
//		 플레이어 미사일(원) - 적(원)
//		 플레이어            - 아이템
//		 맵 경계(선)		 - 플레이어 (left, right, top, bottom)
class Missile;
class Rocket;
class Collider: public GameObject
{
//collider : 충돌하는 물체		obstacle : 충돌받는 물체
private:
	RECT colliderRect;
	RECT obstacleRect;
	FPOINT obstaclePos;
	FPOINT colliderPos;
	bool isCollision;

	Rocket* obstacle;
	Missile* collider;
public:
	bool CollisionCheck();

	void Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);	

	void setObstaclePos(); //적,미사일, 플레이어 위치 받아오기						
	void setColliderPos();
	void setObstacleRect();
	void setColliderRect();

	inline RECT getObstacleRect() { return obstacleRect; }
	inline RECT getColliderRect() { return colliderRect; }
	inline FPOINT getObstaclePos() { return obstaclePos; }
	inline FPOINT getColliderPos(){ return colliderPos; }

};

