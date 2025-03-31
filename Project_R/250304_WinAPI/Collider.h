#pragma once
#include "GameObject.h"
//�浹 : �� �̻���(��)       - �÷��̾� (��)
//		 �� ��ü(��)         - �÷��̾� (��)
//		 �÷��̾� �̻���(��) - ��(��)
//		 �÷��̾�            - ������
//		 �� ���(��)		 - �÷��̾� (left, right, top, bottom)
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
    RECT attackerRect;     // �浹�� �õ��ϴ� ��ü�� �浹 ����
    RECT targetRect;       // �浹 ����� �浹 ����
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

    // �浹 ���� ������Ʈ
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