#pragma once
#include "Singleton.h"
#include "GameObject.h"
#include <vector>


//enum class MissileOwner { PLAYER, ENEMY };
//enum class MissileType { NORMAL, SIGN, LAZER };
//enum class ItemType {A, B, C};
class Missile;
class Rocket;
class Enemy;
class ColliderManager: public Singleton<ColliderManager>
{
private:
    Rocket* rocket;                 // 플레이어
    vector<Enemy*> enemies;         // 적 객체들
    vector<Missile*> missiles;      // 미사일 객체들

    bool isCollision;               // 충돌 발생 여부

public:
    ColliderManager() : rocket(nullptr), isCollision(false) { }

    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);

    void SetRocket(Rocket* r) { rocket = r; }
    void AddEnemy(Enemy* enemy) { if (enemy) enemies.push_back(enemy); }
    void AddMissile(Missile* missile) { if (missile) missiles.push_back(missile); }
    void UpdateCollisionRects();

    // 충돌 검사 함수들
    bool CheckCollision();                          // 모든 충돌 검사
    void CheckPlayerEnemyCollision();               // 플레이어-적 충돌
    void CheckPlayerEnemyMissileCollision();        // 플레이어-적미사일 충돌
    void CheckEnemyPlayerMissileCollision();        // 적-플레이어미사일 충돌
    void UpdateCollisionRects();
    bool GetIsCollision() { return isCollision; }
};

