#include "ColliderManager.h"
#include "CommonFunction.h"
#include "Rocket.h"
#include "Missile.h"
#include "Enemy.h"
#include "State.h"
#include "EnemyState.h"

void ColliderManager::Init()
{
    rocket = nullptr;
    EnemyManager::GetInstance()->Init();
    missiles.clear();
    isCollision = false;
}

void ColliderManager::Release()
{
    if (rocket)
    {
        rocket->Release();
        delete rocket;
        rocket = nullptr;
    }
    
    for (auto& e : enemies)
    {
        if (e->GetIsAlive() == false)
        {
            e->Release();
            delete e;
            e = nullptr;
        }
    }
    EnemyManager::GetInstance()->Release();

    for (auto& m : missiles)
    {
        if(m->GetIsOutOfScreen()== true)
        m->Release();
        delete m;
        m = nullptr;
    }
    missiles.clear();
}

void ColliderManager::Update()
{
    // 충돌 검사 수행
    UpdateCollisionRects();
    CheckCollision();
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

void ColliderManager::UpdateCollisionRects()
{
    // 모든 적의 충돌 RECT 업데이트
    for (auto& enemy : enemies)
    {
        if (enemy && enemy->GetIsAlive())
        {
            enemy->UpdateCollisionRect();
        }
    }

    // 모든 미사일의 충돌 RECT 업데이트
    for (auto& missile : missiles)
    {
        if (missile && missile->isActived)
        {
            missile->UpdateCollisionRect();
        }
    }

    // 로켓의 충돌 RECT 업데이트
    if (rocket)
    {
        rocket->UpdateCollisionRect();
    }
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
            string currState = rocket->GetState();
            if (currState != "Hit" && currState != "Dead")
            {
                isCollision = true;
                // 플레이어와 적의 충돌 처리
                rocket->ChangeState(new HitState());
                // 적의 체력 감소 또는 상태 변경 등 필요한 처리
            }
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

    for (auto& enemy : enemies)
    {
        if (enemy == nullptr || enemy->GetIsAlive() == false) continue;

        if (RectInRect(rocket->GetRect(), enemy->GetRect()))
        {
            isCollision = true;

            // 충돌 발생 시 로켓의 이동 방지 플래그 설정
            rocket->SetCanMove(false);

            // 선택적으로 로켓의 상태 변경
            rocket->ChangeState(new HitState());
            return; // 첫 번째 충돌 후 함수 종료
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
                        enemy->ChangeState(new EnemyDeadState());
                        //적 체력 감소
                        break;
                    case MissileType::SIGN:
                        // 특수 미사일 처리 
                        enemy->ChangeState(new EnemyDeadState());
                        //범위 데미지
                        break;
                    case MissileType::LAZER:
                        // 레이저 미사일 처리 
                        enemy->ChangeState(new EnemyDeadState());
                        missile->isActived = true;
                        //관통효과
                        break;
                    }
                }
            }
        }
    }
}

void ColliderManager::CheckPlayerItemCollision()
{
    if (rocket == nullptr) return;

    for (auto& item : items)
    {   
        if (item == nullptr) continue;

        //if (RectInRect(rocket->GetRect(),item->GetRect()))
        //{
        //    isCollision = true;
        //    // 플레이어와 적의 충돌 처리
        //    rocket->ChangeState(new HitState());
        //    // 적의 체력 감소 또는 상태 변경 등 필요한 처리
        //}
    }
}