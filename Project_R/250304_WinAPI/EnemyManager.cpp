#include "EnemyManager.h"  
#include "Enemy.h"  
#include "ColliderManager.h"  

void EnemyManager::Init()
{
    spawnInterval = 2;
    elapsedTime = 0.0f;
    maxEnemies = 10;
    spawnPattern = 0;
    count = 0;

    eState = new EnemyIDLEState();

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
        count = rand() % 3;
        SetSpawnPattern(count);
        return;
    }
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
}

void EnemyManager::AddEnemy()
{
    if (vecEnemys.size() >= maxEnemies) return;

    float spawnX = 10.0f + (rand() % 5) * 60.0f;
    float spawnY = 80.0f + (rand() % 3) * 90.0f;

    SmallEnemy* enemy = new SmallEnemy();
    enemy->Init(spawnX, spawnY);
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
		for (int i = 0; i < maxEnemies; i++)
		{
			SmallEnemy* enemy = new SmallEnemy();
			enemy->Init(10.0f + 60.0f * (i % 5),
				80.0f + 90.0f * (i / 5));
			enemy->UpdateCollisionRect();
			ColliderManager::GetInstance()->AddEnemy(enemy);
			vecEnemys.push_back(enemy);
		}
		break;

	case 1:
		for (int i = 0; i < maxEnemies; i++)
		{
			BigEnemy* enemy = new BigEnemy();
			enemy->Init(rand() % WINSIZE_X, 0, 1);
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
			enemy->Init(WINSIZE_X/2, WINSIZE_Y/2, 2);
            enemy->loadImage();
			enemy->UpdateCollisionRect();
			ColliderManager::GetInstance()->AddEnemy(enemy);
			vecEnemys.push_back(enemy);
		}
		break;
	}
}
