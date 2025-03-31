#include "GameObject.h"

enum class eCollisionType { RECT, ELLIPSE };

class Collider : public GameObject
{
private:
    eCollisionType collisionType;
    // �浹 ���� ������ (RECT �Ǵ� ���� ������)
    // �浹 �̺�Ʈ ó�� �Լ� ������
public:
    void CheckCollision(Collider* other);
    void SetCollisionType(eCollisionType type);
    // �̺�Ʈ ó�� �Լ� ���/ȣ��
};

// ColliderManager.h
class ColliderManager : public Singleton<ColliderManager> {
private:
    std::vector<Collider*> colliders;
public:
    void Update();
    // Collider ���� �Լ�
};

// ColliderManager.cpp
void ColliderManager::Update() {
    for (auto collider1 : colliders) {
        for (auto collider2 : colliders) {
            if (collider1 != collider2 && collider1->CheckCollision(collider2)) {
                // �浹 �̺�Ʈ ó��
            }
        }
    }
}

// Collider.cpp
void Collider::CheckCollision(Collider* other) {
    if (collisionType == eCollisionType::RECT) {
        // RectInRect �浹 �˻�
    }
    else if (collisionType == eCollisionType::ELLIPSE) {
        // ElipseInElipse �浹 �˻�
    }
}