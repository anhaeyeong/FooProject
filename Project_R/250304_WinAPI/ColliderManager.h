#pragma once
#include "Singleton.h"
#include "Collider.h"
#include <vector>

//ColliderManager�� ������ �浹 �˻縦 ���� ����
//��,�÷��̾�,�̻��Ͽ��� �浹���� ����

//�浹 ��
struct CollisionPair
{
	eColliderType type1;
	eColliderType type2;

	CollisionPair(eColliderType t1, eColliderType t2): type1(t1), type2(t2) {}
};

class ColliderManager : public Singleton<typename ColliderManager>
{
private:
	std::vector<Collider*> colliders;
	std::vector<CollisionPair> collisionPairs; 

	bool IsValidCollisionPair(eColliderType type1, eColliderType type2);
	void InitCollisionMatrix();  // �浹 ��Ʈ������ �浹 ������ ��� ����Ǽ��� �ʱ�ȭ

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

    // �浹ü ���� �� ����
    Collider* CreateCollider(eColliderType type = eColliderType::ROCKET);
    void DestroyCollider(Collider* collider);

    // �浹 �� ���
    void AddCollisionPair(eColliderType type1, eColliderType type2);

    // Ư�� ��ü�� �浹 ���� ��ü�� ã��
    std::vector<GameObject*> GetCollidingObjects(GameObject* obj);

    // Ư�� ��ü�� Ư�� Ÿ���� ��ü�� �� �浹 ���� ��ü�� ã��
    std::vector<GameObject*> GetCollidingObjectsByType(GameObject* obj, eColliderType targetType);

    // �浹 ���� Ȯ��
    bool IsColliding(GameObject* obj);
};