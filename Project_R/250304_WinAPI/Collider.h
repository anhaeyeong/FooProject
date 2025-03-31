#pragma once
#include "GameObject.h"
//충돌 : 적 미사일(원)       - 플레이어 (원)
//		 적 개체(원)         - 플레이어 (원)
//		 플레이어 미사일(원) - 적(원)
//		 플레이어            - 아이템
//		 맵 경계(선)		 - 플레이어 (left, right, top, bottom)
enum class eColliderType
{
    ENEMY,
    ROCKET,
    PLAYER_MISSILE,
    ENEMY_MISSILE,
    ITEM
};

class Missile;
class Enemy;
class Rocket;
class Collider : public GameObject
{
private:
    RECT attackerRect;     // 충돌을 시도하는 주체의 충돌 영역
    RECT targetRect;       // 충돌 대상의 충돌 영역
    eColliderType attackerType;
    eColliderType targetType;
    bool isCollision;

public:
    void Init();
    void Update();
    void Render(HDC hdc);

    Collider(eColliderType attacker = eColliderType::ROCKET,
        eColliderType target = eColliderType::ENEMY);
    ~Collider();

    bool CheckCollision();

    // 충돌 영역 업데이트
    void UpdateAttackerRect(float x, float y, float width, float height);
    void UpdateTargetRect(float x, float y, float width, float height);

    inline void SetAttackerType(eColliderType type) { attackerType = type; }
    inline void SetTargetType(eColliderType type) { targetType = type; }

    inline eColliderType GetAttackerType() const { return attackerType; }
    inline eColliderType GetTargetType() const { return targetType; }

    inline RECT GetAttackerRect() const { return attackerRect; }
    inline RECT GetTargetRect() const { return targetRect; }

    inline bool IsColliding() const { return isCollision; }
};