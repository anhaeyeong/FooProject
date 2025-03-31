#include "ColliderManager.h"

void ColliderManager::Init()
{
    colliders.resize(50);
    for (auto& collider : colliders)
    {
        collider = new Collider();
        collider->Init();
        collider->SetActive(false); // �ʱ⿡�� ��Ȱ��ȭ
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

    // ��� �浹ü�� �浹 ���� �ʱ�ȭ
    for (auto& collider : colliders)
    {
        if (collider && collider->IsActive())
        {
            collider->SetCollision(false);
        }
    }

    // �浹 �˻�
    for (size_t i = 0; i < colliders.size(); i++)
    {
        if (!colliders[i] || !colliders[i]->IsActive()) continue;

        for (size_t j = i + 1; j < colliders.size(); j++)
        {
            if (!colliders[j] || !colliders[j]->IsActive()) continue;

            // �浹 ��Ʈ���� Ȯ��
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
    // �÷��̾�� �浹�ϴ� Ÿ�Ե� (�÷��̾� - ��, �÷��̾� - ���̻���, �÷��̾� - ������)
    AddCollisionPair(eColliderType::ROCKET, eColliderType::ENEMY_NORMAL);
    AddCollisionPair(eColliderType::ROCKET, eColliderType::ENEMY_FAST);
    AddCollisionPair(eColliderType::ROCKET, eColliderType::ENEMY_BOSS);
    AddCollisionPair(eColliderType::ROCKET, eColliderType::MISSILE_ENEMY_NORMAL);
    AddCollisionPair(eColliderType::ROCKET, eColliderType::ITEM_POWER);
    AddCollisionPair(eColliderType::ROCKET, eColliderType::ITEM_SHIELD);

    // �÷��̾� �̻��ϰ� �浹�ϴ� Ÿ�Ե� (�÷��̾� �̻��� - ��)
    AddCollisionPair(eColliderType::MISSILE_PLAYER_NORMAL, eColliderType::ENEMY_NORMAL);
    AddCollisionPair(eColliderType::MISSILE_PLAYER_NORMAL, eColliderType::ENEMY_FAST);
    AddCollisionPair(eColliderType::MISSILE_PLAYER_NORMAL, eColliderType::ENEMY_BOSS);

    AddCollisionPair(eColliderType::MISSILE_PLAYER_SIGN, eColliderType::ENEMY_NORMAL);
    AddCollisionPair(eColliderType::MISSILE_PLAYER_SIGN, eColliderType::ENEMY_FAST);
    AddCollisionPair(eColliderType::MISSILE_PLAYER_SIGN, eColliderType::ENEMY_BOSS);

    AddCollisionPair(eColliderType::MISSILE_PLAYER_LAZER, eColliderType::ENEMY_NORMAL);
    AddCollisionPair(eColliderType::MISSILE_PLAYER_LAZER, eColliderType::ENEMY_FAST);
    AddCollisionPair(eColliderType::MISSILE_PLAYER_LAZER, eColliderType::ENEMY_BOSS);

    // �� ������ �浹
    AddCollisionPair(eColliderType::ROCKET, eColliderType::MAP_BOUNDARY);
    AddCollisionPair(eColliderType::ENEMY_NORMAL, eColliderType::MAP_BOUNDARY);
    AddCollisionPair(eColliderType::ENEMY_FAST, eColliderType::MAP_BOUNDARY);
}

Collider* ColliderManager::CreateCollider(eColliderType type)
{
    // ��Ȱ�� �浹ü ã��
    for (auto& collider : colliders)
    {
        if (!collider->IsActive())
        {
            // ���� �� ��ȯ
            collider->SetActive(true);
            collider->SetType(type);
            return collider;
        }
    }

    // ��� �浹ü�� ��� ���̸� ���� ����
    Collider* newCollider = new Collider(type);
    newCollider->Init();
    newCollider->SetActive(true);
    colliders.push_back(newCollider);

    return newCollider;
}

void ColliderManager::DestroyCollider(Collider* collider)
{
    if (!collider) return;

    // ��Ȱ��ȭ
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

    // ��ü�� �浹ü ã��
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

    // ��ü�� �浹ü ã��
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

    // �浹 ���� �ٸ� ��ü�� ã��
    for (auto& collider : colliders)
    {
        if (collider && collider->IsActive() && collider->IsColliding() &&
            collider != objCollider && collider->GetOwner() != nullptr)
        {
            // �� �� �浹ü�� �浹 �������� Ȯ��
            if (IsValidCollisionPair(objCollider->GetType(), collider->GetType()))
            {
                // �浹 ���� ��ü�� Ȯ��
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

    // Ư�� Ÿ�Ը� ���͸�
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