#pragma once
#include "GameObject.h"
//Collider Ŭ������ �浹üũ�� �Ѵ�.
//�浹�� �߻��ϸ� �̺�Ʈ �߻��Ѵ�.
//��,�÷��̾�,�̻��ϵ��� �̺�Ʈ�� ������ ���� ó���Ѵ�.

enum class eColliderType
{
    ROCKET,              //�÷��̾�

    // �� Ÿ��
    ENEMY_NORMAL,        // �Ϲ� ��
    ENEMY_FAST,          // ���� ��
    ENEMY_BOSS,          // ���� ��

    // �̻��� Ÿ�� 
    MISSILE_PLAYER_NORMAL,  // �÷��̾� �Ϲ� �̻���
    MISSILE_PLAYER_SIGN,    // �÷��̾� ���� �̻���
    MISSILE_PLAYER_LAZER,   // �÷��̾� ������ �̻���
    MISSILE_ENEMY_NORMAL,   // �� �Ϲ� �̻���

    // ������ Ÿ��
    ITEM_POWER,          // Ÿ�Ժ��� ������
    ITEM_SHIELD,         // ����     ������
    
    MAP_BOUNDARY         // �� ���
};

class Missile;
class Enemy;
class Rocket;
class Collider : public GameObject
{
private:
      RECT rect;               // �浹 ����
    eColliderType type;      // �浹ü Ÿ��
    GameObject* owner;       // ������ ��ü
    bool isCollision;        // �浹 ����
    bool isActive;           // Ȱ��ȭ ����

    bool isCollision;//�浹   ����
    bool isActive;   //Ȱ��ȭ ����(���������� ����)

public:
    void Init();
    void Update();
    void Render(HDC hdc);

    Collider();
    ~Collider();

    //�浹ü �˻�
    bool CheckCollision(const Collider* other) const;

    //�浹 ���� ������Ʈ
    void UpdateRect(float x, float y, float width, float height);

    //�浹ü Ÿ�� ����,Ȯ��
    eColliderType GetType() const { return type; }
    void SetType(eColliderType t) { type = t; }

    //�浹ü ������ ����,Ȯ��
    GameObject* GetOwner() const { return owner; }
    void SetOwner(GameObject* o) { owner = o; }

    //�浹ü ���� Ȯ��
    RECT GetRect() const { return rect; }

    //�浹 ���� Ȯ��
    bool IsColliding() const { return isCollision; }
    void SetCollision(bool state) { isCollision = state; }

    // Ȱ��ȭ ���� ��ȸ/����
    bool IsActive() const { return isActive; }
    void SetActive(bool state) { isActive = state; }
};