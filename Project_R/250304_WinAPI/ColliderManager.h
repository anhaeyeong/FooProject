#pragma once
#include "Singleton.h"
#include "GameObject.h"
#include <vector>

//�浹�� Ž���ؼ� �浹�˻� ������ collider���� ���� 
//enum class MissileOwner { PLAYER, ENEMY };
//enum class MissileType { NORMAL, SIGN, LAZER };
//enum class ItemType {A, B, C};
class Missile;
class Rocket;
class Enemy;
class ColliderManager: public Singleton<ColliderManager>
{
private:
	vector<RECT*> playerCollision; //�÷��̾�<->��, �÷��̾� <-> �̻���
	vector<RECT*> enemyCollision; //��<->�̻��� , �� <-> �÷��̾�
	vector<RECT*> missileCollision; // �÷��̾� �̻���<-> ��, �� �̻���<-> �÷��̾�

	Missile* missileOwner; //getOwner�� ������ �÷��̾����� ����

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

