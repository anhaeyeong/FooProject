#include "GameObject.h"

enum class eCollisionType { RECT, ELLIPSE };

class Collider : public GameObject
{
private:
    eCollisionType collisionType;
    // 충돌 영역 데이터 (RECT 또는 원형 데이터)
    // 충돌 이벤트 처리 함수 포인터
public:
    void CheckCollision(Collider* other);
    void SetCollisionType(eCollisionType type);
    // 이벤트 처리 함수 등록/호출
};

// ColliderManager.h
class ColliderManager : public Singleton<ColliderManager> {
private:
    std::vector<Collider*> colliders;
public:
    void Update();
    // Collider 관리 함수
};

// ColliderManager.cpp
void ColliderManager::Update() {
    for (auto collider1 : colliders) {
        for (auto collider2 : colliders) {
            if (collider1 != collider2 && collider1->CheckCollision(collider2)) {
                // 충돌 이벤트 처리
            }
        }
    }
}

// Collider.cpp
void Collider::CheckCollision(Collider* other) {
    if (collisionType == eCollisionType::RECT) {
        // RectInRect 충돌 검사
    }
    else if (collisionType == eCollisionType::ELLIPSE) {
        // ElipseInElipse 충돌 검사
    }
}