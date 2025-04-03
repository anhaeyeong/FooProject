#include "EnemyManager.h"
#include "Enemy.h"
#include "ColliderManager.h"

void EnemyManager::Init()
{
    spawnInterval = 2;
    elapsedTime = 0.0f;
    maxEnemies = 10;
    spawnPattern = 0;  

	vecEnemys.resize(maxEnemies);
    SetSpawnPattern(1);
}

void EnemyManager::Release()
{
    for (int i = 0; i < vecEnemys.size(); i++)
    {
        delete vecEnemys[i];
    }
    vecEnemys.clear();
}

void EnemyManager::Update()
{
    elapsedTime += 0.016f;

    if (elapsedTime >= spawnInterval)
    {
        elapsedTime = 0.0f;
        if (vecEnemys.size() < maxEnemies)
        {
            AddEnemy();
        }
    }

    for (int i = 0; i < vecEnemys.size(); i++)
    {
        vecEnemys[i]->Update();

        if (vecEnemys[i]->GetPos().y + 50> WINSIZE_Y)
        {
            vecEnemys[i]->SetPosition(vecEnemys[i]->GetPos().x, 0);
        }
    }
}

void EnemyManager::Render(HDC hdc)
{
    for (int i = 0; i < vecEnemys.size(); i++)
    {
        vecEnemys[i]->Render(hdc);
    }
}

void EnemyManager::AddEnemy()
{
    float spawnX = 0.0f;
    float spawnY = 0.0f;

    spawnX = 10.0f + (rand() % 5) * 60.0f;
    spawnY = 80.0f + (rand() % 3) * 90.0f;
    SetSpawnPattern(1);
}

void EnemyManager::SetSpawnPattern(int pattern)
{
    switch (pattern)
    {
    case 0:
        for (int i = 0; i < maxEnemies; i++)
        {
            vecEnemys[i] = new SmallEnemy();
            vecEnemys[i]->Init(10.0f + 60.0f * (i % 5),
                80.0f + 90.0f * (i / 5));
            vecEnemys[i]->UpdateCollisionRect();
            ColliderManager::GetInstance()->AddEnemy(vecEnemys[i]);

        }
        break;

    case 1:
        for (int i = 0; i < maxEnemies; i++)
        {
            vecEnemys[i] = new BigEnemy();
            vecEnemys[i]->Init(rand() % WINSIZE_X, rand() % WINSIZE_Y, 1);
            vecEnemys[i]->loadImage();
            vecEnemys[i]->UpdateCollisionRect();
            ColliderManager::GetInstance()->AddEnemy(vecEnemys[i]);
        }
        break;

    case 2:
        for (int i = 0; i < maxEnemies; i++)
        {
            vecEnemys[i] = new BossEnemy();
            vecEnemys[i]->Init(50.0f * (i % 5), 100.0f + 50.0f * (i / 5), 2);
            vecEnemys[i]->UpdateCollisionRect();
            ColliderManager::GetInstance()->AddEnemy(vecEnemys[i]);
        }
        break;
    }
}


