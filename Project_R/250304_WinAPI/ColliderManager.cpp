#include "ColliderManager.h"

void ColliderManager::Init()
{
    colliders.resize(50);
    for (auto& collider : colliders)
    {
        collider = new Collider();
        collider->Init();
        collider->SetActive(false); // 초기에는 비활성화
    }

    InitCollisionMatrix();
}

void ColliderManager::Release()
{
    if (colliders.empty()) return;

    for (auto& collider : colliders)
    {
        if (collider)
        {
            collider->Release();
            delete collider;
            collider = nullptr;
        }
    }
    colliders.clear();
    collisionPairs.clear();
}

void ColliderManager::Update()
{
    if (colliders.empty()) return;

    // 모든 충돌체의 충돌 상태 초기화
    for (auto& collider : colliders)
    {
        if (collider && collider->IsActive())
        {
            collider->SetCollision(false);
        }
    }

    // 충돌 검사
    for (size_t i = 0; i < colliders.size(); i++)
    {
        if (!colliders[i] || !colliders[i]->IsActive()) continue;

        for (size_t j = i + 1; j < colliders.size(); j++)
        {
            if (!colliders[j] || !colliders[j]->IsActive()) continue;

            // 충돌 매트릭스 확인
            if (IsValidCollisionPair(colliders[i]->GetType(), colliders[j]->GetType()))
            {
                if (colliders[i]->CheckCollision(colliders[j]))
                {
                    colliders[i]->SetCollision(true);
                    colliders[j]->SetCollision(true);
                }
            }
        }
    }
}

void ColliderManager::Render(HDC hdc)
{
    if (colliders.empty()) return;

    for (auto& collider : colliders)
    {
        if (collider && collider->IsActive())
        {
            collider->Render(hdc);
        }
    }
}

void ColliderManager::InitCollisionMatrix()
{
    // 플레이어와 충돌하는 타입들 (플레이어 - 적, 플레이어 - 적미사일, 플레이어 - 아이템)
    AddCollisionPair(eColliderType::ROCKET, eColliderType::ENEMY_NORMAL);
    AddCollisionPair(eColliderType::ROCKET, eColliderType::ENEMY_FAST);
    AddCollisionPair(eColliderType::ROCKET, eColliderType::ENEMY_BOSS);
    AddCollisionPair(eColliderType::ROCKET, eColliderType::MISSILE_ENEMY_NORMAL);
    AddCollisionPair(eColliderType::ROCKET, eColliderType::ITEM_POWER);
    AddCollisionPair(eColliderType::ROCKET, eColliderType::ITEM_SHIELD);

    // 플레이어 미사일과 충돌하는 타입들 (플레이어 미사일 - 적)
    AddCollisionPair(eColliderType::MISSILE_PLAYER_NORMAL, eColliderType::ENEMY_NORMAL);
    AddCollisionPair(eColliderType::MISSILE_PLAYER_NORMAL, eColliderType::ENEMY_FAST);
    AddCollisionPair(eColliderType::MISSILE_PLAYER_NORMAL, eColliderType::ENEMY_BOSS);

    AddCollisionPair(eColliderType::MISSILE_PLAYER_SIGN, eColliderType::ENEMY_NORMAL);
    AddCollisionPair(eColliderType::MISSILE_PLAYER_SIGN, eColliderType::ENEMY_FAST);
    AddCollisionPair(eColliderType::MISSILE_PLAYER_SIGN, eColliderType::ENEMY_BOSS);

    AddCollisionPair(eColliderType::MISSILE_PLAYER_LAZER, eColliderType::ENEMY_NORMAL);
    AddCollisionPair(eColliderType::MISSILE_PLAYER_LAZER, eColliderType::ENEMY_FAST);
    AddCollisionPair(eColliderType::MISSILE_PLAYER_LAZER, eColliderType::ENEMY_BOSS);

    // 맵 경계와의 충돌
    AddCollisionPair(eColliderType::ROCKET, eColliderType::MAP_BOUNDARY);
    AddCollisionPair(eColliderType::ENEMY_NORMAL, eColliderType::MAP_BOUNDARY);
    AddCollisionPair(eColliderType::ENEMY_FAST, eColliderType::MAP_BOUNDARY);
}

Collider* ColliderManager::CreateCollider(eColliderType type)
{
    // 비활성 충돌체 찾기
    for (auto& collider : colliders)
    {
        if (!collider->IsActive())
        {
            // 설정 후 반환
            collider->SetActive(true);
            collider->SetType(type);
            return collider;
        }
    }

    // 모든 충돌체가 사용 중이면 새로 생성
    Collider* newCollider = new Collider(type);
    newCollider->Init();
    newCollider->SetActive(true);
    colliders.push_back(newCollider);

    return newCollider;
}

void ColliderManager::DestroyCollider(Collider* collider)
{
    if (!collider) return;

    // 비활성화
    collider->SetActive(false);
    collider->SetCollision(false);
    collider->SetOwner(nullptr);
}

void ColliderManager::AddCollisionPair(eColliderType type1, eColliderType type2)
{
    collisionPairs.push_back(CollisionPair(type1, type2));
}

bool ColliderManager::IsValidCollisionPair(eColliderType type1, eColliderType type2)
{
    for (const auto& pair : collisionPairs)
    {
        if ((pair.type1 == type1 && pair.type2 == type2) ||
            (pair.type1 == type2 && pair.type2 == type1))
        {
            return true;
        }
    }
    return false;
}

bool ColliderManager::IsColliding(GameObject* obj)
{
    if (!obj) return false;

    // 객체의 충돌체 찾기
    for (const auto& collider : colliders)
    {
        if (collider && collider->IsActive() && collider->GetOwner() == obj)
        {
            if (collider->IsColliding())
            {
                return true;
            }
        }
    }

    return false;
}

std::vector<GameObject*> ColliderManager::GetCollidingObjects(GameObject* obj)
{
    std::vector<GameObject*> result;

    if (!obj) return result;

    // 객체의 충돌체 찾기
    Collider* objCollider = nullptr;

    for (auto& collider : colliders)
    {
        if (collider && collider->IsActive() && collider->GetOwner() == obj)
        {
            objCollider = collider;
            break;
        }
    }

    if (!objCollider || !objCollider->IsColliding()) return result;

    // 충돌 중인 다른 객체들 찾기
    for (auto& collider : colliders)
    {
        if (collider && collider->IsActive() && collider->IsColliding() &&
            collider != objCollider && collider->GetOwner() != nullptr)
        {
            // 이 두 충돌체가 충돌 가능한지 확인
            if (IsValidCollisionPair(objCollider->GetType(), collider->GetType()))
            {
                // 충돌 여부 구체적 확인
                if (objCollider->CheckCollision(collider))
                {
                    result.push_back(collider->GetOwner());
                }
            }
        }
    }

    return result;
}

std::vector<GameObject*> ColliderManager::GetCollidingObjectsByType(GameObject* obj, eColliderType targetType)
{
    std::vector<GameObject*> result;
    std::vector<GameObject*> allCollisions = GetCollidingObjects(obj);

    // 특정 타입만 필터링
    for (auto& collider : colliders)
    {
        if (collider && collider->IsActive() && collider->GetType() == targetType)
        {
            for (auto collidingObj : allCollisions)
            {
                if (collider->GetOwner() == collidingObj)
                {
                    result.push_back(collidingObj);
                    break;
                }
            }
        }
    }

    return result;
}