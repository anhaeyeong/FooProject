#pragma once
#include "GameObject.h"
//Collider 클래스는 충돌체크만 한다.
//충돌이 발생하면 이벤트 발생한다.
//적,플레이어,미사일들이 이벤트를 받으면 각자 처리한다.

enum class eColliderType
{
    ROCKET,              //플레이어

    // 적 타입
    ENEMY_NORMAL,        // 일반 적
    ENEMY_FAST,          // 빠른 적
    ENEMY_BOSS,          // 보스 적

    // 미사일 타입 
    MISSILE_PLAYER_NORMAL,  // 플레이어 일반 미사일
    MISSILE_PLAYER_SIGN,    // 플레이어 유도 미사일
    MISSILE_PLAYER_LAZER,   // 플레이어 레이저 미사일
    MISSILE_ENEMY_NORMAL,   // 적 일반 미사일

    // 아이템 타입
    ITEM_POWER,          // 타입변경 아이템
    ITEM_SHIELD,         // 무적     아이템
    
    MAP_BOUNDARY         // 맵 경계
};

class Missile;
class Enemy;
class Rocket;
class Collider : public GameObject
{
private:
      RECT rect;               // 충돌 영역
    eColliderType type;      // 충돌체 타입
    GameObject* owner;       // 소유자 객체
    bool isCollision;        // 충돌 상태
    bool isActive;           // 활성화 상태

    bool isCollision;//충돌   상태
    bool isActive;   //활성화 상태(무적판정에 쓸것)

public:
    void Init();
    void Update();
    void Render(HDC hdc);

    Collider();
    ~Collider();

    //충돌체 검사
    bool CheckCollision(const Collider* other) const;

    //충돌 영역 업데이트
    void UpdateRect(float x, float y, float width, float height);

    //충돌체 타입 설정,확인
    eColliderType GetType() const { return type; }
    void SetType(eColliderType t) { type = t; }

    //충돌체 소유자 설정,확인
    GameObject* GetOwner() const { return owner; }
    void SetOwner(GameObject* o) { owner = o; }

    //충돌체 영역 확인
    RECT GetRect() const { return rect; }

    //충돌 여부 확인
    bool IsColliding() const { return isCollision; }
    void SetCollision(bool state) { isCollision = state; }

    // 활성화 상태 조회/설정
    bool IsActive() const { return isActive; }
    void SetActive(bool state) { isActive = state; }
};