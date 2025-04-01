#include "ColliderManager.h"
#include "CommonFunction.h"
#include "Rocket.h"
#include "Missile.h"
#include "Enemy.h"
#include "State.h"

void ColliderManager::Init()
{
    rocket = nullptr;
    enemies.clear();
    missiles.clear();
    isCollision = false;
}

void ColliderManager::Update()
{
    // 충돌 검사 수행
    CheckCollision();
}

bool ColliderManager::CheckCollision()
{
    isCollision = false;

    // 플레이어와 적 충돌 검사
    CheckPlayerEnemyCollision();

    // 플레이어와 적 미사일 충돌 검사
    CheckPlayerEnemyMissileCollision();

    // 적과 플레이어 미사일 충돌 검사
    CheckEnemyPlayerMissileCollision();

    return isCollision;
}

void ColliderManager::CheckPlayerEnemyCollision()
{
    if (rocket == nullptr) return;

    for (auto& enemy : enemies)
    {   //적이 nullptr 이거나 죽으면 스킵
        if (enemy == nullptr || enemy->GetIsAlive() == false) continue;

        if (RectInRect(rocket->GetRect(), enemy->GetRect()))
        {
            isCollision = true;
            // 플레이어와 적의 충돌 처리
            rocket->ChangeState(new HitState());
            // 적의 체력 감소 또는 상태 변경 등 필요한 처리
        }
    }
}

void ColliderManager::CheckPlayerEnemyMissileCollision()
{
    if (rocket == nullptr) return;

    for (auto& missile : missiles)
    {   // 미사일이 nullptr이거나 비활성화 상태면 스킵
        if (missile == nullptr || missile->isActived == false) continue;

        // 적 미사일만 검사
        if (missile->GetOwner() == MissileOwner::ENEMY)
        {
            if (RectInRect(rocket->GetRect(), missile->GetRect()))
            {
                isCollision = true;
                missile->isActived = false;
                // 플레이어 피격 처리
                rocket->ChangeState(new HitState());
            }
        }
    }
}

void ColliderManager::CheckEnemyPlayerMissileCollision()
{
    for (auto& missile : missiles)
    {
        if (missile == nullptr || missile->isActived == false) continue;

        // 플레이어 미사일만 검사
        if (missile->GetOwner() == MissileOwner::PLAYER)
        {
            for (auto& enemy : enemies)
            {
                if (enemy == nullptr || enemy->GetIsAlive() == false) continue;

                if (RectInRect(missile->GetRect(), enemy->GetRect()))
                {
                    isCollision = true;
                    missile->isActived = false;

                    // 미사일 타입에 따른 적 처리
                    switch (missile->GetType())
                    {
                    case MissileType::NORMAL:
                        // 일반 미사일 처리
                        enemy->SetIsAlive(false);
                        //적 체력 감소
                        break;
                    case MissileType::SIGN:
                        // 특수 미사일 처리 
                        enemy->SetIsAlive(false);
                        //범위 데미지
                        break;
                    case MissileType::LAZER:
                        // 레이저 미사일 처리 
                        enemy->SetIsAlive(false);
                        missile->isActived = true;
                        //관통효과
                        break;
                    }
                }
            }
        }
    }
}

void ColliderManager::Render(HDC hdc)
{
    // 충돌 상태: 빨간색 , 기본 상태: 초록색
    HPEN pen = CreatePen(PS_SOLID, 2, isCollision ? RGB(255, 0, 0) : RGB(0, 255, 0));
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

    if (rocket)
    {
        RECT rc = rocket->GetRect();
        Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
    }

    for (auto& enemy : enemies)
    {
        if (enemy == nullptr || enemy->GetIsAlive() == false) continue;

        RECT rc = enemy->GetRect();
        Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
    }

    for (auto& missile : missiles)
    {
        if (missile == nullptr || missile->isActived == false) continue;

        RECT rc = missile->GetRect();
        Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
    }

    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
}

void ColliderManager::Release()
{
    rocket = nullptr;
    enemies.clear();
    missiles.clear();
}