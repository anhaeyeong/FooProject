#include "EnemyManager.h"  
#include "Enemy.h"  
#include "ColliderManager.h"
#include "MissileFactory.h"

void EnemyManager::Init()
{
    spawnInterval = 2;
    elapsedTime = 0.0f;
    winDelay = 0.0f;
    maxEnemies = 10;
    spawnPattern = 0;
    count = 0;
    loopCounter = 0;
    isWin = false;
    eState = new EnemyIDLEState();

    missileFactory = EnemyMissileFactory::GetInstance();
    missileFactory->Init();

    SetSpawnPattern(0); // �� �ʱ� ����
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

    // �� ����
    for (int i = vecEnemys.size() - 1; i >= 0; i--)
    {
        if (vecEnemys[i] && vecEnemys[i]->GetIsAlive()==false)
        {
            vecEnemys.erase(vecEnemys.begin() + i);
        }
    }



    if (vecEnemys.empty())
    {
        if (loopCounter == 10) {
            count = 3;
			loopCounter++;
        }
        else if(loopCounter < 10)
        {
            count = rand() % 3;
            loopCounter++;
        }
        else
        {
            winDelay += TimerManager::GetInstance()->GetDeltaTime();
            if (winDelay >= 2.0f)
                isWin = true;
        }

        SetSpawnPattern(count);
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
    // ���� �� ����
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

    case 3:
        for (int i = 0; i < 1; i++)
        {
            BossEnemy* enemy = new BossEnemy();
            enemy->Init(WINSIZE_X / 2, 100, 2);
            enemy->Notice();
            enemy->loadImage();
            enemy->UpdateCollisionRect();
            ColliderManager::GetInstance()->AddEnemy(enemy);
            vecEnemys.push_back(enemy);
        }
        break;
	}
}
