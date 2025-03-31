#pragma once
#include "Singleton.h"
#include "Collider.h"
#include <vector>

//ColliderManager는 누구와 충돌 검사를 할지 결정
//적,플레이어,미사일에게 충돌정보 전달

//충돌 쌍
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
	void InitCollisionMatrix();  // 충돌 매트릭스에 충돌 가능한 모든 경우의수를 초기화

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

    // 충돌체 생성 및 관리
    Collider* CreateCollider(eColliderType type = eColliderType::ROCKET);
    void DestroyCollider(Collider* collider);

    // 충돌 쌍 등록
    void AddCollisionPair(eColliderType type1, eColliderType type2);

    // 특정 객체와 충돌 중인 객체들 찾기
    std::vector<GameObject*> GetCollidingObjects(GameObject* obj);

    // 특정 객체와 특정 타입의 객체들 중 충돌 중인 객체들 찾기
    std::vector<GameObject*> GetCollidingObjectsByType(GameObject* obj, eColliderType targetType);

    // 충돌 여부 확인
    bool IsColliding(GameObject* obj);
};