#include "ColliderManager.h"
#include "Collider.h"

void ColliderManager::Init()
{
    colliders.resize(50);
    for (auto& collider : colliders)
    {
        collider = new Collider();
        collider->Init();
    }
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
}

void ColliderManager::Update()
{
    if (colliders.empty()) return;

    for (auto& collider : colliders)
    {
        collider->Update();
    }
}

void ColliderManager::Render(HDC hdc)
{
    if (colliders.empty()) return;

    for (auto& collider : colliders)
    {
        if (collider) collider->Render(hdc);
    }
}