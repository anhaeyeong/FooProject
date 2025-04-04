#include "EnemyManager.h"  
#include "Enemy.h"  
#include "ColliderManager.h"
#include "MissileFactory.h"

void EnemyManager::Init()
{
    spawnInterval = 2;
    elapsedTime = 0.0f;
    maxEnemies = 10;
    spawnPattern = 0;
    count = 0;
    
    eState = new EnemyIDLEState();

    missileFactory = EnemyMissileFactory::GetInstance();
    missileFactory->Init();

    SetSpawnPattern(0); // 적 초기 스폰
}

void EnemyManager::Release()
{
    for (int i = 0; i < vecEnemys.size(); i++)
    {
        delete vecEnemys[i];
        vecEnemys[i] = nullptr;
    }
    vecEnemys.clear();

    if (eState)
    {
        delete eState;
        eState = nullptr;
    }

    missileFactory->Release();
}

void EnemyManager::Update()
{
    for (int i = 0; i < vecEnemys.size(); i++)
    {
        if (vecEnemys[i])
        {
            vecEnemys[i]->Update();

            if (vecEnemys[i]->GetPos().y + 50 > WINSIZE_Y)
            {
                vecEnemys[i]->SetPosition(vecEnemys[i]->GetPos().x, 0);
            }
        }
    }

    // 적 제거
    for (int i = vecEnemys.size() - 1; i >= 0; i--)
    {
        if (vecEnemys[i] && vecEnemys[i]->GetIsAlive()==false)
        {
            //delete vecEnemys[i];
            vecEnemys.erase(vecEnemys.begin() + i);
        }
    }

    // 적이 전부 사라졌다면 새로운 패턴 설정
    if (vecEnemys.empty())
    {
        //count = rand() % 4;
        SetSpawnPattern(2);
        return;
    }
    missileFactory->Update();
}

void EnemyManager::Render(HDC hdc)
{
    for (int i = 0; i < vecEnemys.size(); i++)
    {
        if (vecEnemys[i])
        {
            vecEnemys[i]->Render(hdc);
        }
    }
    missileFactory->Render(hdc);
}

void EnemyManager::AddEnemy()
{
    if (vecEnemys.size() >= maxEnemies) return;
    SmallEnemy* enemy = new SmallEnemy();
    enemy->UpdateCollisionRect();
    ColliderManager::GetInstance()->AddEnemy(enemy);

    vecEnemys.push_back(enemy);
}

void EnemyManager::SetSpawnPattern(int pattern)
{
    // 기존 적 삭제
    for (int i = 0; i < vecEnemys.size(); i++)
    {
        delete vecEnemys[i];
        vecEnemys[i] = nullptr;
    }
    vecEnemys.clear();

	switch (pattern)
	{
	case 0:
		for (int i = 0; i < 60; i++)
		{
			SmallEnemy* enemy = new SmallEnemy();
			enemy->Init(WINSIZE_X/4 + 40.0f * (i % 12),
				20.0f + 40.0f * (i % 10) ,0);
            enemy->Notice();
			enemy->UpdateCollisionRect();
			ColliderManager::GetInstance()->AddEnemy(enemy);
			vecEnemys.push_back(enemy);
		}
		break;

	case 1:
		for (int i = 0; i < 30; i++)
		{
			BigEnemy* enemy = new BigEnemy();
			enemy->Init(rand() % WINSIZE_X, 0, 1);
            enemy->Notice();
			enemy->loadImage();
			enemy->UpdateCollisionRect();
			ColliderManager::GetInstance()->AddEnemy(enemy);
			vecEnemys.push_back(enemy);
		}
		break;

	case 2:
		for (int i = 0; i <1; i++)
		{
			BossEnemy* enemy = new BossEnemy();
			enemy->Init(WINSIZE_X/2, 100, 2);
            enemy->Notice();
            enemy->loadImage();
			enemy->UpdateCollisionRect();
			ColliderManager::GetInstance()->AddEnemy(enemy);
			vecEnemys.push_back(enemy);
		}
		break;

    case 3:  
        for (int i = 0; i < 7; i++)
        {
            TrackingEnemy* enemy = new TrackingEnemy();
            enemy->Init(rand() % WINSIZE_X, 50, 7);
            enemy->loadImage();
            enemy->UpdateCollisionRect();
            enemy->Notice();
            ColliderManager::GetInstance()->AddEnemy(enemy);
            vecEnemys.push_back(enemy);
        }
        break;
	}
}
